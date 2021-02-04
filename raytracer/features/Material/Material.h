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
    float ambient = 0.1;
    float diffuse = 0.9;
    float specular = 0.9;
    float shininess = 200.0;

    bool operator==(const Material &other) {
        return this->color == other.color && Helper::compareFloat(this->ambient, other.ambient) &&
                Helper::compareFloat(this->diffuse, other.diffuse) && Helper::compareFloat(this->specular, other.specular) &&
                Helper::compareFloat(this->shininess, other.shininess);
    }

    Tuple lighting(Light light, Point point, Vector eye, Vector normal);

    std::string toString();
};


#endif //RAYTRACER_MATERIAL_H
