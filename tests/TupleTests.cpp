#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "Tuple.h"
#include "Point.h"
#include "Vector.h"

// #include "Color.h"
#include "Constvals.h"

#include <iostream>
#include <format>

TEST(TupleTests, PointTest)
{
    Tuple expected{4, -4, 3, 1};
    Point point{4, -4, 3};
    EXPECT_TRUE(point == expected);
}


TEST(TupleTests, VectorTest)
{
    Tuple expected{4, -4, 3, 0};
    Vector vector{4, -4, 3};
    EXPECT_TRUE(vector == expected);
}


TEST(TupleTests, EqualityTest)
{
    {
        Tuple lhs{4.000009, -4.000009, 3.000009, 1.000009};
        Tuple rhs{4.0, -4.0, 3.0, 1.0};
        EXPECT_TRUE(lhs == rhs);
    }
    {
        Tuple lhs{4.00001, -4.00001, 3.00001, 1.00001};
        Tuple rhs{4.0, -4.0, 3.0, 1.0};
        EXPECT_FALSE(lhs == rhs);
    }
}

TEST(TupleTests, AddTest)
{
    {
        Tuple lhs{3, -2, 5, 1};
        Tuple rhs{-2, 3, 1, 0};
        Tuple expected{1, 1, 6, 1};
        EXPECT_TRUE(lhs + rhs == expected);
    }
}

TEST(TupleTests, SubtractTest)
{
    {
        Tuple lhs{Point{3, 2, 1}};
        Tuple rhs{Point{5, 6, 7}};
        Tuple expected{Vector{-2, -4, -6}};
        EXPECT_TRUE(lhs - rhs == expected);
    }
    {
        Tuple lhs{Point{3, 2, 1}};
        Tuple rhs{Vector{5, 6, 7}};
        Tuple expected{Point{-2, -4, -6}};
        EXPECT_TRUE(lhs - rhs == expected);
    }
    {
        Tuple lhs{Vector{3, 2, 1}};
        Tuple rhs{Vector{5, 6, 7}};
        Tuple expected{Vector{-2, -4, -6}};
        EXPECT_TRUE(lhs - rhs == expected);
    }
}

TEST(TupleTests, NegateTest)
{
    {
        Tuple lhs{Vector{0, 0, 0}};
        Tuple rhs{Vector{1, -2, 3}};
        Tuple expected{Vector{-1, 2, -3}};
        EXPECT_TRUE(lhs - rhs == expected);
    }
    {
        Tuple tup{1, -2, 3, -4};
        Tuple expected{-1, 2, -3, 4};
        EXPECT_TRUE(-tup == expected);
    }
}

TEST(TupleTests, MultiplyScalarTest)
{
    {
        Tuple tup{1, -2, 3, -4};
        Tuple expected{3.5, -7, 10.5, -14};
        float scalar{3.5f};
        EXPECT_TRUE(tup*scalar == expected);

    }
    {
        Tuple tup{1, -2, 3, -4};
        Tuple expected{0.5, -1, 1.5, -2};
        float scalar{0.5f};
        EXPECT_TRUE(tup*scalar == expected);
    }
}

TEST(TupleTests, DivideScalarTest)
{
    {
        Tuple tup{1, -2, 3, -4};
        Tuple expected{0.5, -1, 1.5, -2};
        float scalar{2};
        EXPECT_TRUE(tup/scalar == expected);
    }
    {
        Tuple tup{1, -2, 3, -4};
        float scalar{0};
        Tuple out{tup/scalar};
        EXPECT_TRUE(std::isinf(out.x));
        EXPECT_TRUE(std::isinf(out.y));
        EXPECT_TRUE(std::isinf(out.z));
        EXPECT_TRUE(std::isinf(out.w));
    }
}

TEST(TupleTests, MagnitudeTest)
{
    {
        Tuple tup{Vector{1, 0, 0}};
        float expected{1};
        EXPECT_TRUE(tup.Magnitude() == expected);
    }
    {
        Tuple tup{Vector{0, 1, 0}};
        float expected{1};
        EXPECT_TRUE(tup.Magnitude() == expected);
    }
    {
        Tuple tup{Vector{0, 0, 1}};
        float expected{1};
        EXPECT_TRUE(tup.Magnitude() == expected);
    }
    {
        Tuple tup{Vector{1, 2, 3}};
        float expected{std::sqrt(14.f)};
        EXPECT_TRUE(tup.Magnitude() == expected);
    }
    {
        Tuple tup{Vector{-1, -2, -3}};
        float expected{std::sqrt(14.f)};
        EXPECT_TRUE(tup.Magnitude() == expected);
    }
}

TEST(TupleTests, NormalizeTest)
{
    {
        Tuple tup{Vector{4, 0, 0}};
        Tuple expected{Vector{1, 0, 0}};
        EXPECT_TRUE(tup.Normalize() == expected);
    }
    {
        Tuple tup{Vector{1, 2, 3}};
        Tuple expected{Vector{0.26726, 0.53452, 0.80178}};
        EXPECT_TRUE(tup.Normalize() == expected);
    }
    {
        Tuple tup{Vector{1, 2, 3}};
        float expected{1.0f};
        EXPECT_TRUE(EQF(tup.Normalize().Magnitude(), expected));
    }
}

TEST(TupleTests, CrossTest)
{
    {
        Tuple vecA{Vector{1, 2, 3}};
        Tuple vecB{Vector{2, 3, 4}};
        Tuple expected_axb{Vector{-1, 2, -1}};
        Tuple expected_bxa{Vector{1, -2, 1}};
        EXPECT_TRUE(vecA.Cross(vecB) == expected_axb);
        EXPECT_TRUE(vecB.Cross(vecA) == expected_bxa);
    }
}
