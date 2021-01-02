//
// Created by Max on 2021-01-02.
//

#include <iostream>
#include "raytracer/features/Tuple.h"

struct Projectile {
    Tuple position, velocity;
};

struct Environment {
    Tuple gravity, wind;
};

int main() {
    Environment env;
    env.gravity = Tuple::vector(0, -0.1, 0);
    env.wind = Tuple::vector(-0.01, 0, 0);

    Projectile proj;
    proj.position = Tuple::point(0, 1, 0);
    proj.velocity = Tuple::vector(1, 1, 0).preciseNormalize();

    for (int i = 0; i < 1000; i++) {

    }
}

Projectile tick(Environment env, Projectile proj) {
    Projectile projectile;

    projectile.position = proj.position + proj.velocity;
    projectile.velocity = proj.velocity + env.gravity + env.wind;

    return projectile;
}