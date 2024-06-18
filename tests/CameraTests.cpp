#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include <numbers>

#include "Camera.h"
#include "Ray.h"
#include "Transformations.h"
#include "Matrices.h"
#include "World.h"
#include "Canvas.h"
#include "Light.h"

namespace nums = std::numbers;

TEST(CameraTests, InitializerTest)
{
    {
        unsigned int hsize{160};
        unsigned int vsize{120};
        double fov{nums::pi/2.f};
        Camera c{hsize,vsize,fov};
        EXPECT_EQ(c.hsize, hsize);
        EXPECT_EQ(c.vsize, vsize);
        EXPECT_EQ(c.fov, fov);
        EXPECT_EQ(c.transform, (Identity<double,4>()));
    }
}

TEST(CameraTests, PixelSizeTest)
{
    {
        Camera c{200,125,nums::pi/2.f};
        EXPECT_EQ(c.pixel_dimension,0.01f);
    }
    {
        Camera c{125,200,nums::pi/2.f};
        EXPECT_EQ(c.pixel_dimension,0.01f);
    }
}

TEST(CameraTests, RayThroughPixelTest)
{
    {
        Camera c{201,101,nums::pi/2.f};
        Ray ray{c.RayThroughPixel(100,50)};
        EXPECT_EQ(ray.origin, Point(0,0,0));
        EXPECT_EQ(ray.direction, Vector(0,0,-1));
    }
    {
        Camera c{201,101,nums::pi/2.f};
        Ray ray{c.RayThroughPixel(0,0)};
        EXPECT_EQ(ray.origin, Point(0,0,0));
        EXPECT_EQ(ray.direction, Vector(0.66519,0.33259,-0.66851));
    }
    {
        Matrix4d transform{Transformations::RotationY(nums::pi/4.f) * Transformations::Translation(0,-2,5)};
        Camera c{201,101,nums::pi/2.f,transform};
        Ray ray{c.RayThroughPixel(100,50)};
        EXPECT_EQ(ray.origin, Point(0,2,-5));
        EXPECT_EQ(ray.direction, Vector(std::sqrt(2)/2.f,0.f,-std::sqrt(2)/2.f));
    }
}

TEST(CameraTests, RenderTest)
{
    {
        World world{WorldFactory::DefaultWorld()};
        Point from{0,0,-5};
        Point to{0,0,0};
        Vector up{0,1,0};
        Matrix4d transform{ViewTransform(from, to, up)};
        Camera camera{11,11,nums::pi/2.f,transform};
        Canvas canvas{camera.Render(world)};
        EXPECT_EQ(canvas.PixelAt(5,5), Color(0.38066, 0.47583, 0.2855));
    }
}