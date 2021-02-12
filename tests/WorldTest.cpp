//
// Created by Max on 2021-02-05.
//

#include "gtest/gtest.h"
#include "../raytracer/features/World/World.h"
#include "../raytracer/features/Ray/Ray.h"

// Creating a world
TEST(WorldTests, TestCreateWorld) {
    World world;

    ASSERT_EQ(0, world.objects.size());
//    ASSERT_TRUE(world.light == Light());
}

// The default world
TEST(WorldTests, TestDefaultWorld) {
    Light light(Point(-10, 10, -10), Color(1, 1, 1));
    Sphere s1;
    s1.material.color = Color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    Sphere s2;
    s2.transform.scale(0.5, 0.5, 0.5);

    World world = World::defaultWorld();

    ASSERT_TRUE(light == world.light);
    ASSERT_TRUE(world.contains(s1));
    ASSERT_TRUE(world.contains(s2));
    ASSERT_EQ(2, world.objects.size());
}

// Intersect a world with a ray
TEST(WorldTests, TestWorldRayIntersection) {
    World world = World::defaultWorld();
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    Intersections xs = ray.intersect(&world);

    ASSERT_EQ(4, xs.size());
    ASSERT_EQ(4, xs[0].t);
    ASSERT_EQ(4.5, xs[1].t);
    ASSERT_EQ(5.5, xs[2].t);
    ASSERT_EQ(6, xs[3].t);
}

// Shading an intersection
TEST(WorldTests, TestShading) {
    World world = World::defaultWorld();
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersection i(4, &world.objects[0]);
    Tuple c = world.shadeHit(ray.prepareComputations(i));

    ASSERT_TRUE(Color(0.38066, 0.47583, 0.2855) == c);
}

// Shading an intersection from the inside
TEST(WorldTests, TestShadingInside) {
    World world = World::defaultWorld();
    world.light = Light(Point(0, 0.25, 0), Color(1, 1, 1));
    Ray ray(Point(0, 0, 0), Vector(0, 0, 1));
    Intersection i(0.5, &world.objects[1]);
    Tuple c = world.shadeHit(ray.prepareComputations(i));

    ASSERT_TRUE(Color(0.90498, 0.90498, 0.90498) == c);
}
