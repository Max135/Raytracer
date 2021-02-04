//
// Created by Max on 2021-02-03.
//

#include "Material.h"

Tuple Material::lighting(Light light, Point point, Vector eye, Vector normal) {
    //Combine the surface color with the light's color/intensity
    Tuple effectiveColor = this->color * light.intensity;

    //Find the direction to the light source
    Tuple lightVector = (light.position - point).normalize();

    //Compute the ambient contribution
    Tuple currentAmbient = effectiveColor * this->ambient;

    //lightDotNormal represents the cosine of the angle between the light vector and the normal vector
    //A negative number means the light is on the other side of the surface
    float lightDotNormal = lightVector.dot(normal);

    Tuple currentDiffuse, currentSpecular;
    if(lightDotNormal < 0) {
        currentDiffuse = Color(0, 0, 0);
        currentSpecular = Color(0, 0, 0);
    } else {
        //Compute the diffuse contribution
        currentDiffuse = effectiveColor * this->diffuse * lightDotNormal;

        //reflectDotEye represents the cosine of the angle between the reflection vector and the eye vector
        //A negative number means the light reflects away from the eye
        Tuple reflectVector = (-lightVector).reflectOff(normal);
        float reflectDotEye = reflectVector.dot(eye);

        if(reflectDotEye <= 0) {
            currentSpecular = Color(0, 0, 0);
        } else {
            //Compute the specular contribution
            float factor = pow(reflectDotEye, this->shininess);
            currentSpecular = light.intensity * this->specular * factor;
        }
    }

    return currentAmbient + currentDiffuse + currentSpecular;
}

std::string Material::toString() {
    std::string string;
    string.append("Color: ");
    string.append(this->color.toString());
    string.append("ambient: ");
    string.append(std::to_string(this->ambient));
    string.append("diffuse: ");
    string.append(std::to_string(this->diffuse));
    string.append("specular: ");
    string.append(std::to_string(this->specular));
    string.append("shininess: ");
    string.append(std::to_string(this->shininess));

    return string;
}
