//
// Created by Max on 2021-01-02.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include "raytracer/features/Tuple/Tuples.h"
#include "raytracer/features/Canvas/Canvas.h"
#include "raytracer/features/Matrix/Matrices.h"

struct Projectile {
    Tuple position, velocity;
};

struct Environment {
    Tuple gravity, wind;
};


Projectile tick(Environment, Projectile, Canvas*);
void saveCanvas(Canvas);
void projectileTrajectory();


int main() {
    std::clock_t startTime;
    startTime = std::clock();

    projectileTrajectory();

    clock_t endTime = clock();
    clock_t clockTicksTaken = endTime - startTime;
    double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
    std::cout << std::fixed << "Runtime: " << timeInSeconds << " s." << std::endl;

    return 0;
}

void projectileTrajectory() {
    Environment env;
    env.gravity = Vector(0, -0.1, 0);
    env.wind = Vector(-0.01, 0.01, 0);

    Projectile proj;
    proj.position = Point(0, 1, 0);
    proj.velocity = Vector(6, 10.8, 0).preciseNormalize() * 11.25;

    Canvas canvas(1000, 1000);

    while (proj.position.y > 0) {
        proj = tick(env, proj, &canvas);
//        std::cout << "x: " << proj.position.x << " y: " << proj.position.y << " z: " << proj.position.z << std::endl;
    }

    saveCanvas(canvas);
}

Projectile tick(Environment env, Projectile proj, Canvas* canvas) {
    Projectile projectile;

    projectile.position = proj.position + proj.velocity;
    projectile.velocity = proj.velocity + env.gravity + env.wind;

    Tuple pos = projectile.position;
    canvas->writePixel((int)round(pos.x), canvas->height - (int)round(pos.y), Color(1, 0, 0));

    return projectile;
}

void saveCanvas(Canvas canvas) {
    std::ofstream file("Canvas.ppm");
    file << canvas.toPPM();
    file.close();
}
