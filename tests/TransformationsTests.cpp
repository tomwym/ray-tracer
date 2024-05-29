#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "Transformations.h"
#include "Tuple.h"
#include "Point.h"
#include "Vector.h"

#include <iostream>
#include <cmath>
#include <numbers>

using namespace std::numbers;

TEST(TransformationsTest, TranslationTest)
{
    {
        Matrix4f transform{Transformations::Translation(5,-3,2)};
        Point point{-3,4,5};
        Point expected{2,1,7};
        EXPECT_EQ(transform*point, expected);
    }
    {
        Matrix4f transform{Transformations::Translation(5,-3,2)};
        Point point{-3,4,5};
        Point expected{-8,7,3};
        EXPECT_EQ(transform.Inverse()*point, expected);
    }
    {
        Matrix4f transform{Transformations::Translation(5,-3,2)};
        Vector vec{-3,4,5};
        EXPECT_EQ(transform*vec, vec);
    }
}

TEST(TransformationsTest, ScalingTest)
{
    {
        Matrix4f transform{Transformations::Scaling(2,3,4)};
        Point point{-4,6,8};
        Point expected{-8,18,32};
        EXPECT_EQ(transform*point, expected);
    }
    {
        Matrix4f transform{Transformations::Scaling(2,3,4)};
        Vector vec{-4,6,8};
        Vector expected{-8,18,32};
        EXPECT_EQ(transform*vec, expected);
    }
    {
        Matrix4f transform{Transformations::Scaling(2,3,4)};
        Vector vec{-4,6,8};
        Vector expected{-2,2,2};
        EXPECT_EQ(transform.Inverse()*vec, expected);
    }
    {
        Matrix4f transform{Transformations::Scaling(-1,1,1)};
        Vector vec{2,3,4};
        Vector expected{-2,3,4};
        EXPECT_EQ(transform*vec, expected);
    }
}

TEST(TransformationsTest, RotationTest)
{
    {
        Matrix4f eighth{Transformations::RotationX(pi/4.f)};
        Matrix4f quarter{Transformations::RotationX(pi/2.f)};
        Point point{0,1,0};
        Point expected_eighth{0,sqrt(2)/2.f,std::sqrt(2)/2.f};
        Point expected_quarter{0,0,1};
        EXPECT_EQ(eighth*point, expected_eighth);
        EXPECT_EQ(quarter*point, expected_quarter);
    }
    {
        Matrix4f eighth{Transformations::RotationX(pi/4.f)};
        Point point{0,1,0};
        Point expected_eighth{0,sqrt(2)/2.f,-std::sqrt(2)/2.f};
        EXPECT_EQ(eighth.Inverse()*point, expected_eighth);
    }
    {
        Matrix4f eighth{Transformations::RotationY(pi/4.f)};
        Matrix4f quarter{Transformations::RotationY(pi/2.f)};
        Point point{0,0,1};
        Point expected_eighth{sqrt(2)/2.f,0.f,std::sqrt(2)/2.f};
        Point expected_quarter{1,0,0};
        EXPECT_EQ(eighth*point, expected_eighth);
        EXPECT_EQ(quarter*point, expected_quarter);
    }
    {
        Matrix4f eighth{Transformations::RotationZ(pi/4.f)};
        Matrix4f quarter{Transformations::RotationZ(pi/2.f)};
        Point point{0,1,0};
        Point expected_eighth{-sqrt(2)/2.f,std::sqrt(2)/2.f,0.f};
        Point expected_quarter{-1,0,0};
        EXPECT_EQ(eighth*point, expected_eighth);
        EXPECT_EQ(quarter*point, expected_quarter);
    }
}

TEST(TransformationsTest, ShearingTest)
{
    {
        Matrix4f shear{Transformations::Shearing(1,0,0,0,0,0)};
        Point point{2,3,4};
        Point expected{5,3,4};
        EXPECT_EQ(shear*point, expected);
    }
    {
        Matrix4f shear{Transformations::Shearing(0,1,0,0,0,0)};
        Point point{2,3,4};
        Point expected{6,3,4};
        EXPECT_EQ(shear*point, expected);
    }
    {
        Matrix4f shear{Transformations::Shearing(0,0,1,0,0,0)};
        Point point{2,3,4};
        Point expected{2,5,4};
        EXPECT_EQ(shear*point, expected);
    }
    {
        Matrix4f shear{Transformations::Shearing(0,0,0,1,0,0)};
        Point point{2,3,4};
        Point expected{2,7,4};
        EXPECT_EQ(shear*point, expected);
    }
    {
        Matrix4f shear{Transformations::Shearing(0,0,0,0,1,0)};
        Point point{2,3,4};
        Point expected{2,3,6};
        EXPECT_EQ(shear*point, expected);
    }
    {
        Matrix4f shear{Transformations::Shearing(0,0,0,0,0,1)};
        Point point{2,3,4};
        Point expected{2,3,7};
        EXPECT_EQ(shear*point, expected);
    }
}

TEST(TransformationsTest, ChainingTest)
{
    {
        Point point{1,0,1};
        Matrix4f rotation{Transformations::RotationX(pi/2.f)};
        Matrix4f scaling{Transformations::Scaling(5,5,5)};
        Matrix4f translation{Transformations::Translation(10,5,7)};
        Point point2{rotation*point};
        EXPECT_TRUE(point2 == (Point{1,-1,0}));
        Point point3{scaling*point2};
        EXPECT_TRUE(point3 == (Point{5,-5,0}));
        Point point4{translation*point3};
        EXPECT_TRUE(point4 == (Point{15,0,7}));
    }
    {
        Point point{1,0,1};
        Matrix4f rotation{Transformations::RotationX(pi/2.f)};
        Matrix4f scaling{Transformations::Scaling(5,5,5)};
        Matrix4f translation{Transformations::Translation(10,5,7)};
        Matrix4f transform{translation*scaling*rotation};
        EXPECT_TRUE(transform*point == (Point{15,0,7}));
    }
}