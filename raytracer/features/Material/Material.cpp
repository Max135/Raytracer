//
// Created by Max on 2021-02-03.
//

#include "Material.h"

bool Material::operator==(const Material &other) {
    return this->color == other.color && Helper::compareFloat(this->ambient, other.ambient) &&
           Helper::compareFloat(this->diffuse, other.diffuse) && Helper::compareFloat(this->specular, other.specular) &&
           Helper::compareFloat(this->shininess, other.shininess);
}

Tuple Material::lighting(const Light& light, const Tuple &point, const Tuple &eye, const Tuple &normal, bool inShadow) {
    //Combine the surface color with the light's color/intensity
    Tuple effectiveColor = this->color * light.intensity;

    //Find the direction to the light source
    Tuple lightVector = (light.position - point).normalize();

    //Compute the ambient contribution
    Tuple currentAmbient = effectiveColor * this->ambient;

    //Ignore the specular and diffuse components when inShadow is true
    if (inShadow) return currentAmbient;

    //lightDotNormal represents the cosine of the angle between the light vector and the normal vector
    //A negative number means the light is on the other side of the surface
    double lightDotNormal = lightVector.dot(normal);

    Color currentDiffuse, currentSpecular;
    if (lightDotNormal < 0) {
        currentDiffuse = Color(0, 0, 0);
        currentSpecular = Color(0, 0, 0);
    } else {
        //Compute the diffuse contribution
        currentDiffuse = effectiveColor * this->diffuse * lightDotNormal;

        //reflectDotEye represents the cosine of the angle between the reflection vector and the eye vector
        //A negative number means the light reflects away from the eye
        Tuple reflectVector = (-lightVector).reflectOff(normal);
        double reflectDotEye = reflectVector.dot(eye);

        if (reflectDotEye <= 0) {
            currentSpecular = Color(0, 0, 0);
        } else {
            //Compute the specular contribution
            double factor = pow(reflectDotEye, this->shininess);
            currentSpecular = light.intensity * this->specular * factor;
        }
    }

    return currentAmbient + currentDiffuse + currentSpecular;
}

std::string Material::toString() {
    std::string string;
    string.append("Color: ");
    string.append(this->color.toString());
    string.append("    Ambient: ");
    string.append(std::to_string(this->ambient));
    string.append("  Diffuse: ");
    string.append(std::to_string(this->diffuse));
    string.append("  Specular: ");
    string.append(std::to_string(this->specular));
    string.append("  Shininess: ");
    string.append(std::to_string(this->shininess));

    return string;
}
