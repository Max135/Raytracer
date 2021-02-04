//
// Created by Max on 2021-01-02.
//

#include <iostream>
#include <ctime>
#include <cmath>
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
    const int canvasSize = 700;
    const int wallSize = 7;
    const int wallZ = 10;
    Sphere sphere;
    sphere.transform.shear(1, 0, 0.01, 0, 1, 0).scale(0.5, 1, 1);

    Color color(0, 0, 255);
    Canvas canvas(canvasSize, canvasSize);
    Point rayOrigin(0, 0, -5);
    float pixelSize = (float) wallSize / canvasSize;
    float half = wallSize / 2.0;

    for (int y = 0; y < canvasSize - 1; ++y) {
        float worldY = half - pixelSize * (float) y;
        for (int x = 0; x < canvasSize - 1; ++x) {
            float worldX = -half + pixelSize * (float) x;
            Point position(worldX, worldY, wallZ);
            Ray ray(rayOrigin, (position - rayOrigin).fastNormalize());
            std::vector<Intersection> xs = ray.intersect(&sphere);

            if (!xs.empty()) {
                canvas.writePixel(x, y, color);
            }
        }
    }

    canvas.save();
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
