//
// Created by Max on 2021-01-10.
//

#include "Ray.h"

PreComputation Ray::prepareComputations(const Intersection &intersection) const {
    // Instantiate a data structure for storing some precomputed values
    PreComputation comps;

    // Copy the intersection's properties, for convenience
    comps.t = intersection.t;
    comps.object = intersection.sphere;

    // Precompute some useful values
    comps.point = this->position(comps.t);
    comps.eyeV = -this->direction;
    comps.normalV = comps.object->normalAt(comps.point);

    if (comps.normalV.dot(comps.eyeV) < 0) {
        comps.inside = true;
        comps.normalV = -comps.normalV;
    } else {
        comps.inside = false;
    }

    // After computing and (if appropriate) negating the normal vector...
    comps.overPoint = comps.point + comps.normalV * Helper::getEPSILON();

    return comps;
}

Tuple Ray::position(double time) const {
    return origin + direction * time;
}

//TODO: Figure out the Ray::intersect() and World::shadeHit cluster fuck
Tuple Ray::colorAt(World world) {
    Intersections intersections = this->intersect(&world);
    Intersection intersection = intersections.hit();
    if (intersection.sphere == nullptr) {
        return Color::black();
    } else {
        PreComputation preComps = this->prepareComputations(intersection);
        return world.shadeHit(preComps);
    }
}

Intersections Ray::intersect(Sphere *sphere) {
    Matrix t = sphere->transform.inverse();
    return intersection(this->transform(&t), sphere);
}

Intersections Ray::intersect(World *world) {
    Intersections intersections;
    for (auto &object: world->objects) {
        intersections.append(this->intersect(&object));
    }
    intersections.sort();
    return intersections;
}

Ray Ray::transform(Matrix *transform) const {
    Ray ray(*transform * this->origin, *transform * this->direction);
    return ray;
}

std::vector<Intersection> Ray::intersection(const Ray& ray, Sphere *sphere) {
    Tuple sphereToRay = ray.origin - sphere->origin;

    double a = ray.direction.dot(ray.direction);
    double b = 2 * ray.direction.dot(sphereToRay);
    double c = sphereToRay.dot(sphereToRay) - 1;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return std::vector<Intersection>();

    double squareRoot = sqrt(discriminant);

    double t1 = (-b - squareRoot) / (2 * a);
    double t2 = (-b + squareRoot) / (2 * a);


    std::vector<Intersection> vector;
    if (t1 > t2) {
        vector.emplace_back(t2, sphere);
        vector.emplace_back(t1, sphere);
    } else {
        vector.emplace_back(t1, sphere);
        vector.emplace_back(t2, sphere);
    }

    return vector;
}

std::string Ray::toString() const {
    std::string string;
    string.append("Origin: ");
    string.append(this->origin.toString());
    string.append(" Direction: ");
    string.append(this->direction.toString());
    return string;
}
