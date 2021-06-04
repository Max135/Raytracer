//
// Created by Max on 2021-02-05.
//

#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H


#include <vector>
#include "../Light/Light.h"
#include "../Shape/Shapes.h"
#include "../Ray/PreComputation.h"

class World {
public:
    Light light;
    std::vector<Sphere> objects;

    World();

    static World defaultWorld();

    bool contains(const Sphere &sphere);

    Tuple shadeHit(const PreComputation& comps);

    bool isShadowed(const Tuple& point);
};


#endif //RAYTRACER_WORLD_H
