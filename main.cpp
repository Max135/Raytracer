//
// Created by Max on 2021-01-02.
//

#include <iostream>
#include <ctime>
#include <cmath>
#include <thread>
#include "raytracer/features/Tuple/Tuples.h"
#include "raytracer/features/Canvas/Canvas.h"
#include "raytracer/features/Matrix/Matrices.h"
#include "raytracer/features/Ray/Ray.h"
#include "raytracer/features/Intersection/Intersection.h"
#include "raytracer/features/Shape/Shapes.h"
#include "raytracer/features/Camera/Camera.h"

struct Projectile {
    Tuple position, velocity;
};

struct Environment {
    Tuple gravity, wind;
};


//World ray tracing
void renderWorld();

//Sphere ray tracing
void traceSphere();
void traceSphereThreads();
void writePixel(Intersections xs, Ray *ray, Canvas *canvas, Light *light, int x, int y);
void calculateColisions(int canvasSize, double half, double pixelSize, double wallZ, const Point& rayOrigin, Sphere *sphere, Canvas *canvas, Light *light, int y);

//Projectile trajectory
void projectileTrajectory();
Projectile tick(Environment, Projectile, Canvas *);

int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

//    projectileTrajectory();
//    traceSphere();
//    traceSphereThreads();
    renderWorld();

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Runtime: " << elapsed_seconds.count() << "s\n";

    return 0;
}


/*
 * Updated implementation of the ray tracer to render a world
 */

void renderWorld() {
    Sphere floor;
    floor.transform = Transform::scaling(10, 0.01, 10);
    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;

    Sphere leftWall;
    leftWall.transform = leftWall.transform.translate(0, 0, 5).rotateY(-M_PI_4).rotateX(M_PI_2).scale(10, 0.01, 10);
    leftWall.material = floor.material;

    Sphere rightWall;
    rightWall.transform = rightWall.transform.translate(0, 0, 5).rotateY(M_PI_4).rotateX(M_PI_2).scale(10, 0.01, 10);
    rightWall.material = floor.material;
    
    Sphere middle;
    middle.transform = Transform::translation(-0.5, 1, 0.5);
    middle.material.color = Color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;
    
    Sphere right;
    right.transform = right.transform.translate(1.5, 0.5, -0.5).scale(0.5, 0.5, 0.5);
    right.material.color = Color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    Sphere left;
    left.transform = left.transform.translate(-1.5, 0.33, -0.75).scale(0.33, 0.33, 0.33);
    left.material.color = Color(1, 0.8, 0.1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;

    World world;
    world.objects.push_back(floor);
    world.objects.push_back(leftWall);
    world.objects.push_back(rightWall);
    world.objects.push_back(middle);
    world.objects.push_back(right);
    world.objects.push_back(left);

    world.light = Light(Point(-10, 10, -10), Color(1, 1, 1));

    Camera camera(1000, 500, M_PI / 3);
    camera.transform = Transform::viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

    Canvas canvas = camera.render(world);
    canvas.save();
}


/*
 * First real implementation of the ray tracer to render a sphere
 */

void traceSphere() {
    const int canvasSize = 1000;
    const int wallSize = 7;
    const int wallZ = 10;

    Sphere sphere;
    sphere.material.color = Color(1, 0.2, 1);
    sphere.transform.shear(1, 0, 0.01, 0, 1, 0).scale(0.5, 1, 1);

    Canvas canvas(canvasSize, canvasSize);

    Light light(Point(-10, 10, -10), Color(1, 1, 1));

    Point rayOrigin(0, 0, -5);

    double pixelSize = (double) wallSize / canvasSize;
    double half = wallSize / 2.0;

    for (int y = 0; y < canvasSize - 1; ++y) {
        if (y % 100 == 0)
            std::cout << y << std::endl;

        double worldY = half - pixelSize * (double) y;
//        calculateColisions(canvasSize, half, pixelSize, worldY, wallZ, rayOrigin, &sphere, &canvas, &light, y);
        for (int x = 0; x < canvasSize - 1; ++x) {
            double worldX = -half + pixelSize * (double) x;
            Point position(worldX, worldY, wallZ);
            Ray ray(rayOrigin, (position - rayOrigin).normalize());
            Intersections xs = ray.intersect(&sphere);

            if (!xs.empty()) {
                Intersection hit = xs[0];
                Tuple point = ray.position(hit.t);
                Tuple normal = hit.sphere->normalAt(point);
                Tuple eye = -(ray.direction);

                canvas.writePixel(x, y, hit.sphere->material.lighting(light, point, eye, normal));
            }
        }
    }

    canvas.save();
}

//TODO: https://stackoverflow.com/questions/16438099/high-level-gpu-programming-in-c
//https://thrust.github.io/
//http://boostorg.github.io/compute/

void traceSphereThreads() {
    const int threadNb = 10;
    const int canvasSize = 1000;
    const int wallSize = 7;
    const int wallZ = 10;

    Sphere sphere;
    sphere.material.color = Color(1, 0, 1);
//    sphere.transform.shear(1, 0, 0.01, 0, 1, 0).scale(0.5, 1, 1);

    Canvas canvas(canvasSize, canvasSize);

    Light light(Point(-10, 10, -10), Color(1, 1, 1));

    Point rayOrigin(0, 0, -5);

    double pixelSize = (double) wallSize / canvasSize;
    double half = wallSize / 2.0;

    for (int y = 0; y < canvasSize - 1; y+=threadNb) {
        if (y % 100 == 0)
            std::cout << y << std::endl;

        std::vector<std::thread> threads;
        for (int limit = y; limit < y + threadNb; limit++) {
            std::thread thread(calculateColisions, canvasSize, half, pixelSize, wallZ, rayOrigin, &sphere,
                               &canvas, &light, limit);
            threads.push_back(std::move(thread));
//          calculateColisions(canvasSize, half, pixelSize, worldY, wallZ, rayOrigin, &sphere, &canvas, &light, y);
        }
        for(auto & thread : threads) {
            thread.join();
        }
    }

    canvas.save();
}

void calculateColisions(int canvasSize, double half, double pixelSize, double wallZ, const Point& rayOrigin, Sphere *sphere, Canvas *canvas, Light *light, int y) {
    double worldY = half - pixelSize * (double) y;
    for (int x = 0; x < canvasSize - 1; ++x) {
        double worldX = -half + pixelSize * (double) x;
        Point position(worldX, worldY, wallZ);
        Ray ray(rayOrigin, (position - rayOrigin).normalize());
        Intersections xs = ray.intersect(sphere);

        if (!xs.empty()) {
            writePixel(xs, &ray, canvas, light, x, y);
        }
    }
}

void writePixel(Intersections xs, Ray *ray, Canvas *canvas, Light *light, int x, int y) {
    Intersection hit = xs[0];
    Tuple point = ray->position(hit.t);
    Tuple normal = hit.sphere->normalAt(point);
    Tuple eye = -(ray->direction);

    canvas->writePixel(x, y, hit.sphere->material.lighting(*light, point, eye, normal));
}


/*
 * First program to calculate a projectile's trajectory and displaying it on a canvas
 */

void projectileTrajectory() {
    Environment env;
    env.gravity = Vector(0, -0.1, 0);
    env.wind = Vector(-0.01, 0.01, 0);

    Projectile proj;
    proj.position = Point(0, 1, 0);
    proj.velocity = Vector(6, 10.8, 0).normalize() * 11.25;

    Canvas canvas(1000, 1000);

    while (proj.position.y > 0) {
        proj = tick(env, proj, &canvas);
//        std::cout << "x: " << proj.position.x << " y: " << proj.position.y << " z: " << proj.position.z << std::endl;
    }

    canvas.save();
}

Projectile tick(Environment env, Projectile proj, Canvas *canvas) {
    Projectile projectile;

    projectile.position = proj.position + proj.velocity;
    projectile.velocity = proj.velocity + env.gravity + env.wind;

    Tuple pos = projectile.position;
    canvas->writePixel((int) round(pos.x), canvas->height - (int) round(pos.y), Color(1, 0, 0));

    return projectile;
}
