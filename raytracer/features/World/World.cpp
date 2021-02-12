//
// Created by Max on 2021-02-05.
//

#include "World.h"

World::World() {
    light = Light();
}

World World::defaultWorld() {
    World world;
    Light light(Point(-10, 10, -10), Color(1, 1, 1));
    Sphere s1;
    s1.material.color = Color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    Sphere s2;
    s2.transform.scale(0.5, 0.5, 0.5);

    world.objects.push_back(s1);
    world.objects.push_back(s2);
    world.light = light;

    return world;
}

bool World::contains(const Sphere &sphere) {
    for (Sphere &object : this->objects) {
        if (object == sphere)
            return true;
    }
    return false;
}
