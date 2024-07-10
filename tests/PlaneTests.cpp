#include <gtest/gtest.h>
#include "Plane.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"

TEST(PlaneTests, NormalTest)
{
    {
        Plane p;
        Vector n1{p.Normal(Point{0,0,0})};
        Vector n2{p.Normal(Point{10,0,-10})};
        Vector n3{p.Normal(Point{-5,0,150})};
        EXPECT_EQ(n1, Vector(0,1,0));
        EXPECT_EQ(n2, Vector(0,1,0));
        EXPECT_EQ(n3, Vector(0,1,0));
    }
}

TEST(PlaneTests, IntersectionTest)
{
    // Parallel to plane
    {
        Plane p;
        Ray r{Point{0,10,0}, Vector{0,0,1}};
        auto xs{p.Intersects(r)};
        EXPECT_EQ(xs.size(), 0);
    }
    // Coplanar to plane
    {
        Plane p;
        Ray r{Point{0,0,0}, Vector{0,0,1}};
        auto xs{p.Intersects(r)};
        EXPECT_EQ(xs.size(), 0);
    }
    // Ray intersects plane from above
    {
        Plane p;
        Ray r{Point{0,1,0}, Vector{0,-1,0}};
        auto xs{p.Intersects(r)};
        EXPECT_EQ(xs.size(), 1);
        EXPECT_EQ(xs[0].t, 1);
        // EXPECT_EQ(xs[0].geometry)
    }
    // Ray intersects plane from below
    {
        Plane p;
        Ray r{Point{0,-1,0}, Vector{0,1,0}};
        auto xs{p.Intersects(r)};
        EXPECT_EQ(xs.size(), 1);
        EXPECT_EQ(xs[0].t, 1);
    }
}