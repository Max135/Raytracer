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

struct Projectile {
    Tuple position, velocity;
};

struct Environment {
    Tuple gravity, wind;
};


Projectile tick(Environment, Projectile, Canvas *);

void projectileTrajectory();

void traceSphere();

void writePixel(std::vector<Intersection> xs, Ray *ray, Canvas *canvas, Light *light, int x, int y);
void calculateColisions(int canvasSize, float half, float pixelSize, float worldY, float wallZ, const Point& rayOrigin, Sphere *sphere, Canvas *canvas, Light *light, int y);


int main() {
    std::clock_t startTime;
    startTime = std::clock();

//    projectileTrajectory();
    traceSphere();

    clock_t endTime = clock();
    clock_t clockTicksTaken = endTime - startTime;
    double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
    std::cout << std::fixed << "Runtime: " << timeInSeconds << " s." << std::endl;

    return 0;
}

//TODO: https://stackoverflow.com/questions/16438099/high-level-gpu-programming-in-c
//https://thrust.github.io/
//http://boostorg.github.io/compute/

void traceSphere() {
    const int canvasSize = 5000;
    const int wallSize = 7;
    const int wallZ = 10;

    Sphere sphere;
    sphere.material.color = Color(0, 0, 1);
    sphere.transform.shear(1, 0, 0.01, 0, 1, 0).scale(0.5, 1, 1);

    Canvas canvas(canvasSize, canvasSize);

    Light light(Point(-10, 10, -10), Color(1, 1, 1));

    Point rayOrigin(0, 0, -5);

    float pixelSize = (float) wallSize / canvasSize;
    float half = wallSize / 2.0;

    for (int y = 0; y < canvasSize - 1; y+=10) {
        if (y % 100 == 0)
            std::cout << y << std::endl;

        std::vector<std::thread> threads;
        for (int limit = y; limit < y + 10; limit++) {
            float worldY = half - pixelSize * (float) y;
            std::thread thread(calculateColisions, canvasSize, half, pixelSize, worldY, wallZ, rayOrigin, &sphere,
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

void calculateColisions(int canvasSize, float half, float pixelSize, float worldY, float wallZ, const Point& rayOrigin, Sphere *sphere, Canvas *canvas, Light *light, int y) {
    for (int x = 0; x < canvasSize - 1; ++x) {
        float worldX = -half + pixelSize * (float) x;
        Point position(worldX, worldY, wallZ);
        Ray ray(rayOrigin, (position - rayOrigin).normalize());
        std::vector<Intersection> xs = ray.intersect(sphere);

        if (!xs.empty()) {
            writePixel(xs, &ray, canvas, light, x, y);
        }
    }
}

void writePixel(std::vector<Intersection> xs, Ray *ray, Canvas *canvas, Light *light, int x, int y) {
    Intersection hit = xs[0];
    Tuple point = ray->position(hit.t);
    Tuple normal = hit.sphere->normalAt(point);
    Tuple eye = -(ray->direction);

    canvas->writePixel(x, y, hit.sphere->material.lighting(*light, point, eye, normal));
}

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
