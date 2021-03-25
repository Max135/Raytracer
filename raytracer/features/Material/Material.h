//
// Created by Max on 2021-02-03.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "../Tuple/Tuples.h"
#include "../Helper.h"
#include "../Light/Light.h"

class Material {
public:
    Color color = Color(1, 1, 1);
    double ambient = 0.1;
    double diffuse = 0.9;
    double specular = 0.9;
    double shininess = 200.0;

    bool operator==(const Material &other);

    Tuple lighting(Light light, const Tuple &point, const Tuple &eye, const Tuple &normal);

    std::string toString();
};


#endif //RAYTRACER_MATERIAL_H
