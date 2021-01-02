//
// Created by Max on 2021-01-02.
//

#include <iostream>
#include <ctime>
#include "raytracer/features/Tuple/Tuple.h"

struct Projectile {
    Tuple position, velocity;
};

struct Environment {
    Tuple gravity, wind;
};

Projectile tick(Environment, Projectile);

int main() {
    std::clock_t startTime;
    double duration;

    startTime = std::clock();

    Environment env;
    env.gravity = Tuple::vector(0, -0.1, 0);
    env.wind = Tuple::vector(-0.11, 0, 0);

    Projectile proj;
    proj.position = Tuple::point(0, 1, 0);
    proj.velocity = Tuple::vector(1, 2, 0).preciseNormalize();

    for (int i = 0; i < 100; i++) {
        proj = tick(env, proj);
        std::cout << "x: " << proj.position.x << " y: " << proj.position.y << " z: " << proj.position.z << std::endl;

        if (proj.position.y <= 0) break;
    }

    clock_t endTime = clock();
    clock_t clockTicksTaken = endTime - startTime;
    double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
    std::cout << std::fixed << "Runtime: " << timeInSeconds << std::endl;

    return 0;
}

Projectile tick(Environment env, Projectile proj) {
    Projectile projectile;

    projectile.position = proj.position + proj.velocity;
    projectile.velocity = proj.velocity + env.gravity + env.wind;

    return projectile;
}