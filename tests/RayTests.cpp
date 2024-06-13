#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Transformations.h"

#include <iostream>

TEST(RayTests, RayConstructorTest)
{
    {
        Point origin{1,2,3};
        Vector direction{4,5,6};
        Ray ray{origin, direction};
        EXPECT_TRUE(ray.origin == origin);
        EXPECT_TRUE(ray.direction == direction);
    }
}

TEST(RayTests, PositionTest)
{
    {
        Point origin{2,3,4};
        Vector direction{1,0,0};
        Ray ray{origin, direction};
        EXPECT_TRUE(ray.Position(0) == Point(2,3,4));
        EXPECT_TRUE(ray.Position(1) == Point(3,3,4));
        EXPECT_TRUE(ray.Position(-1) == Point(1,3,4));
        EXPECT_TRUE(ray.Position(2.5) == Point(4.5,3,4));
    }
}

TEST(RayTests, IntersectTest)
{
    {
        Ray ray{Point(0,0,-5), Vector(0,0,1)};
        auto intersect{ray.Intersects(Sphere{})};

        EXPECT_EQ(intersect.size(), 2);
        EXPECT_EQ(intersect[0].t, 4.f);
        EXPECT_EQ(intersect[1].t, 6.f);
    }
    {
        Ray ray{Point(0,1,-5), Vector(0,0,1)};
        auto intersect{ray.Intersects(Sphere{})};
        EXPECT_EQ(intersect.size(), 2);
        EXPECT_EQ(intersect[0].t, 5.f);
        EXPECT_EQ(intersect[1].t, 5.f);
    }
    {
        // misses sphere
        Ray ray{Point(0,2,-5), Vector(0,0,1)};
        auto intersect{ray.Intersects(Sphere{})};
        EXPECT_EQ(intersect.size(), 0);
    }
    {
        // origin within sphere
        Ray ray{Point(0,0,0), Vector(0,0,1)};
        auto intersect{ray.Intersects(Sphere{})};
        EXPECT_EQ(intersect.size(), 2);
        EXPECT_EQ(intersect[0].t, -1.f);
        EXPECT_EQ(intersect[1].t, 1.f);
    }
    {
        // sphere behind ray
        Ray ray{Point(0,0,5), Vector(0,0,1)};
        auto intersect{ray.Intersects(Sphere{})};
        EXPECT_EQ(intersect.size(), 2);
        EXPECT_EQ(intersect[0].t, -6.f);
        EXPECT_EQ(intersect[1].t, -4.f);
    }
}

TEST(RayTests, TransformTest)
{
    // translating a ray
    {
        Ray ray{Point(1,2,3), Vector(0,1,0)};
        Matrix4f transform(Transformations::Translation(3,4,5));
        Ray r2{ray.Transform(transform)};
        EXPECT_TRUE(r2.origin == Point(4,6,8));
        EXPECT_TRUE(r2.direction == Vector(0,1,0));
    }
    // scaling a ray
    {
        Ray ray{Point(1,2,3), Vector(0,1,0)};
        Matrix4f transform(Transformations::Scaling(2,3,4));
        Ray r2{ray.Transform(transform)};
        EXPECT_TRUE(r2.origin == Point(2,6,12));
        EXPECT_TRUE(r2.direction == Vector(0,3,0));
    }
}