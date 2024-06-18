#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "Material_t.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Light.h"

TEST(MaterialTests, DefaultInitializerTest)
{
    {
        Material_t mat;
        EXPECT_EQ(mat.ambient, 0.1f);
        EXPECT_EQ(mat.diffuse, 0.9f);
        EXPECT_EQ(mat.specular, 0.9f);
        EXPECT_EQ(mat.shininess, 200.f);
    }
}

TEST(MaterialTests, LightingTest)
{
    {
        Material_t mat;
        Point position{0,0,0};
        Vector eye{0,0,-1};
        Vector norm{0,0,-1};
        Light light{Point{0,0,-10},Color{1,1,1}};
        EXPECT_EQ(Lighting(mat,light,position,eye,norm,false), Color(1.9f,1.9f,1.9f));
    }
    {
        Material_t mat;
        Point position{0,0,0};
        double sq2{std::sqrt(2)/2.f};
        Vector eye{0,sq2,-sq2};
        Vector norm{0,0,-1};
        Light light{Point{0,0,-10},Color{1,1,1}};
        EXPECT_EQ(Lighting(mat,light,position,eye,norm,false), Color(1.f,1.f,1.f));
    }
    {
        Material_t mat;
        Point position{0,0,0};
        Vector eye{0,0,-1};
        Vector norm{0,0,-1};
        Light light{Point{0,10,-10},Color{1,1,1}};
        EXPECT_EQ(Lighting(mat,light,position,eye,norm,false), Color(0.7364f,0.7364f,0.7364f));
    }
    {
        Material_t mat;
        Point position{0,0,0};
        double sq2{std::sqrt(2)/2.f};
        Vector eye{0,-sq2,-sq2};
        Vector norm{0,0,-1};
        Light light{Point{0,10,-10},Color{1,1,1}};
        EXPECT_EQ(Lighting(mat,light,position,eye,norm,false), Color(1.6364f,1.6364f,1.6364f));
    }
    {
        Material_t mat;
        Point position{0,0,0};
        Vector eye{0,0,-1};
        Vector norm{0,0,-1};
        Light light{Point{0,0,-10},Color{1,1,1}};
        EXPECT_EQ(Lighting(mat,light,position,eye,norm,false), Color(0.1f,0.1f,0.1f));
    }
    {
        Material_t mat;
        Point position{0,0,0};
        Vector eye{0,0,-1};
        Vector norm{0,0,-1};
        Light light{Point{0,0,-10},Color{1,1,1}};
        EXPECT_EQ(Lighting(mat,light,position,eye,norm,true), Color(0.1f,0.1f,0.1f));
    }
}
