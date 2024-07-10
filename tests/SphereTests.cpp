#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "Sphere.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Transformations.h"

#include <iostream>

auto TestGeometry() -> GeometryPtr {
    return std::make_unique<Sphere>();
}

TEST(SphereTests, TransformTest)
{
    {
        GeometryPtr sphere{TestGeometry()};
        EXPECT_EQ(sphere->Transform(), (Identity<double, 4>()));
    }
    {
        GeometryPtr sphere{TestGeometry()};
        Matrix4d transform{Transformations::Translation(2,3,4)};
        sphere->Transform(transform);
        EXPECT_EQ(sphere->Transform(), transform);
    }
}

TEST(SphereTests, IntersectionTest)
{
    {
        Ray ray{Point(0,0,-5), Vector(0,0,1)};
        GeometryPtr sphere{TestGeometry()};
        sphere->Transform(Transformations::Scaling(2,2,2));
        auto xs{sphere->Intersects(ray)};
        ASSERT_EQ(xs.size(), 2);
        EXPECT_EQ(xs[0].t,3);
        EXPECT_EQ(xs[1].t,7);
    }
    {
        Ray ray{Point(0,0,-5), Vector(0,0,1)};
        GeometryPtr sphere{TestGeometry()};
        sphere->Transform(Transformations::Translation(5,0,0));
        auto xs{sphere->Intersects(ray)};
        ASSERT_EQ(xs.size(), 0);
    }
}

TEST(SphereTests, NormalTest)
{
    {
        GeometryPtr sphere{TestGeometry()};
        Point p{1,0,0};
        Vector v{1,0,0};
        EXPECT_EQ(sphere->Normal(p),v);
    }
    {
        GeometryPtr sphere{TestGeometry()};
        Point p{0,1,0};
        Vector v{0,1,0};
        EXPECT_EQ(sphere->Normal(p),v);
    }
    {
        GeometryPtr sphere{TestGeometry()};
        Point p{0,0,1};
        Vector v{0,0,1};
        EXPECT_EQ(sphere->Normal(p),v);
    }
    {
        GeometryPtr sphere{TestGeometry()};
        double val{std::sqrt(3)/3.f};
        Point p{val,val,val};
        Vector v{val,val,val};
        EXPECT_EQ(sphere->Normal(p),v);
    }
    {
        GeometryPtr sphere{TestGeometry()};
        double val{std::sqrt(3)};
        double valdiv3{val/3.f};
        Point p{val,val,val};
        Vector v{valdiv3,valdiv3,valdiv3};
        EXPECT_EQ(sphere->Normal(p),v);
    }
}

TEST(SphereTests, MaterialTest)
{
    {
        GeometryPtr sphere{TestGeometry()};
        EXPECT_EQ(sphere->Material(), Material_t{});
    }
    {
        GeometryPtr sphere{TestGeometry()};
        Material_t m;
        m.ambient = 1.f;
        sphere->Material(m);
        EXPECT_EQ(sphere->Material(), m);
    }
}