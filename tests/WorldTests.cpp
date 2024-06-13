#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "World.h"
#include "Point.h"
#include "Geometry.h"
#include "Material.h"
#include "Light.h"
#include "Transformations.h"
#include "Ray.h"

TEST(WorldTests, BasicConstructionTest)
{
    {
        World world{WorldFactory::DefaultWorld()};
        EXPECT_EQ(world.light->position, Point(-10,10,-10));
        EXPECT_EQ(world.light->intensity, Color(1,1,1));
        EXPECT_EQ(world.geometries.size(), 2);
        Material_t mat;
        mat.color = Color{0.8,1.0,0.6};
        mat.diffuse = 0.7f;
        mat.specular = 0.2f;
        EXPECT_EQ(world.geometries[0]->Material(), mat);
        EXPECT_EQ(world.geometries[1]->Transform(), Transformations::Scaling(0.5,0.5,0.5));
    }
}

TEST(WorldTests, IntersectionTest)
{
    {
        World world{WorldFactory::DefaultWorld()};
        Ray ray{Point{0,0,-5},Vector{0,0,1}};
        auto xs{world.Intersect(ray)};
        EXPECT_EQ(xs.size(),4);
        EXPECT_EQ(xs[0].t,4.f);
        EXPECT_EQ(xs[1].t,4.5f);
        EXPECT_EQ(xs[2].t,5.5f);
        EXPECT_EQ(xs[3].t,6.f);
    }
}

TEST(WorldTests, ShadeHitTest)
{
    {
        World world{WorldFactory::DefaultWorld()};
        Ray ray{Point{0,0,-5},Vector{0,0,1}};
        GeometryPtr geom{world.geometries.front()->Clone()};
        Intersection i{4,std::move(geom)};
        IntersectionComputation comp{i.PrepareComputations(ray)};
        Color c{world.ShadeHit(comp)};
        EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
    }
    {
        World world{WorldFactory::DefaultWorld()};
        world.light = std::make_unique<Light>(Point{0,0.25,0},Color{1,1,1});
        Ray ray{Point{0,0,0},Vector{0,0,1}};
        GeometryPtr geom{world.geometries[1]->Clone()};
        Intersection i{0.5,std::move(geom)};
        IntersectionComputation comp{i.PrepareComputations(ray)};
        Color c{world.ShadeHit(comp)};
        EXPECT_EQ(c, Color(0.90498, 0.90498, 0.90498));
    }
}

TEST(WorldTests, ColorAtTest)
{
    {
        World world{WorldFactory::DefaultWorld()};
        Ray ray{Point{0,0,-5},Vector{0,1,0}};
        Color c{world.ColorAt(ray)};
        EXPECT_EQ(c, Color(0,0,0));
    }
    {
        // Correct intersection with outside of sphere
        World world{WorldFactory::DefaultWorld()};
        Ray ray{Point{0,0,-5},Vector{0,0,1}};
        Color c{world.ColorAt(ray)};
        EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
    }
    {
        // Ray origin within sphere, detect correct sphere outside
        World world{WorldFactory::DefaultWorld()};
        world.geometries[0]->Material().ambient = 1;
        world.geometries[1]->Material().ambient = 1;
        Ray ray{Point{0,0,0.75},Vector{0,0,-1}};
        Color c{world.ColorAt(ray)};
        EXPECT_EQ(c, world.geometries[1]->Material().color);
    }
}