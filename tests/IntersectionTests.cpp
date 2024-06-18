#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;


#include "Sphere.h"
#include "Intersection.h"
#include "Ray.h"
#include "Transformations.h"

TEST(IntersectionTests, IntersectionTest)
{
    {
        Sphere s;
        Intersection i{3.5,std::make_unique<Sphere>(s)};
        EXPECT_EQ(i.t, 3.5);
        EXPECT_TRUE(*dynamic_cast<Sphere*>(i.geometry.get()) == s);
    }
}

TEST(IntersectionTests, IntersectionsTest)
{
    {
        Sphere s;
        Intersection i1{1,std::make_unique<Sphere>(s)};
        Intersection i2{2,std::make_unique<Sphere>(s)};
        Intersections aggregate{i1, i2};
        EXPECT_EQ(aggregate.size(), 2);
        EXPECT_EQ(aggregate[0].t, 1.f);
        EXPECT_EQ(aggregate[1].t, 2.f);
    }
}

TEST(IntersectionTests, HitTest)
{
    {
        Sphere s;
        Intersection i1{1,std::make_unique<Sphere>(s)};
        Intersection i2{2,std::make_unique<Sphere>(s)};
        Intersections xs{i1, i2};

        EXPECT_EQ(Hit(xs), i1);
    }
}

TEST(IntersectionTests, ComputationsStructTest)
{
    {
        Ray ray{Point{0,0,-5},Vector{0,0,1}};
        Sphere s;
        Intersection i{4,std::make_unique<Sphere>(s)};
        IntersectionComputation computations{i.PrepareComputations(ray)};

        EXPECT_EQ(computations.intersection->t, i.t);
        EXPECT_EQ(*dynamic_cast<Sphere*>(computations.intersection->geometry.get()), s);
        EXPECT_EQ(*computations.point, Point(0,0,-1));
        EXPECT_EQ(*computations.eyev, Vector(0,0,-1));
        EXPECT_EQ(*computations.normalv, Vector(0,0,-1));
    }
}

TEST(IntersectionTests, PrepareComputationsInsideOutTest)
{
    {
        Ray ray{Point{0,0,-5},Vector{0,0,1}};
        Sphere s;
        Intersection i{4,std::make_unique<Sphere>(s)};
        IntersectionComputation computations{i.PrepareComputations(ray)};
        EXPECT_EQ(computations.inside, false);
    }
    {
        Ray ray{Point{0,0,0},Vector{0,0,1}};
        Sphere s;
        Intersection i{1,std::make_unique<Sphere>(s)};
        IntersectionComputation computations{i.PrepareComputations(ray)};
        EXPECT_EQ(*computations.point, Point(0,0,1));
        EXPECT_EQ(*computations.eyev, Vector(0,0,-1));
        EXPECT_EQ(*computations.normalv, Vector(0,0,-1));
        EXPECT_EQ(computations.inside, true);
    }
}

TEST(IntersectionTests, OverPointTest)
{
    {
        Ray ray{Point{0,0,-5},Vector{0,0,1}};
        Matrix4d transform{Transformations::Translation(0,0,1)};
        Sphere s;
        s.Transform(transform);
        Intersection i{5,std::make_unique<Sphere>(s)};
        IntersectionComputation comps {i.PrepareComputations(ray)};
        EXPECT_TRUE(comps.over_point->z < -EPSILON/2.f);
        EXPECT_TRUE(comps.point->z > comps.over_point->z);
    }

}