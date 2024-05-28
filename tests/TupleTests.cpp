#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "Tuple.h"
#include "Color.h"
#include "Constvals.h"

#include <iostream>
#include <format>

TEST(TupleTests, PointTest)
{
    TupleF expected{4, -4, 3, 1};
    EXPECT_TRUE(PointF(4, -4, 3) == expected);
}

TEST(TupleTests, VectorTest)
{
    TupleF expected{4, -4, 3, 0};
    EXPECT_TRUE(VectorF(4, -4, 3) == expected);
}

TEST(TupleTests, EqualityTest)
{
    {
        TupleF lhs{4.000009, -4.000009, 3.000009, 1.000009};
        TupleF rhs{4.0, -4.0, 3.0, 1.0};
        EXPECT_TRUE(lhs == rhs);
    }
    {
        TupleF lhs{4.00001, -4.00001, 3.00001, 1.00001};
        TupleF rhs{4.0, -4.0, 3.0, 1.0};
        EXPECT_FALSE(lhs == rhs);
    }
}

TEST(TupleTests, AddTest)
{
    {
        TupleF lhs{3, -2, 5, 1};
        TupleF rhs{-2, 3, 1, 0};
        TupleF expected{1, 1, 6, 1};
        EXPECT_TRUE(lhs + rhs == expected);
    }
    {
        TupleF lhs{3, -2, 5, 1};
        TupleF rhs{-2, 3, 1, 0};
        TupleF expected{1, 1, 6, 1};
        lhs += rhs;
        EXPECT_TRUE(lhs == expected);
    }
}

TEST(TupleTests, SubtractTest)
{
    {
        TupleF lhs{PointF(3, 2, 1)};
        TupleF rhs{PointF(5, 6, 7)};
        TupleF expected{VectorF(-2, -4, -6)};
        EXPECT_TRUE(lhs - rhs == expected);
    }
    {
        TupleF lhs{PointF(3, 2, 1)};
        TupleF rhs{VectorF(5, 6, 7)};
        TupleF expected{PointF(-2, -4, -6)};
        EXPECT_TRUE(lhs - rhs == expected);
    }
    {
        TupleF lhs{VectorF(3, 2, 1)};
        TupleF rhs{VectorF(5, 6, 7)};
        TupleF expected{VectorF(-2, -4, -6)};
        EXPECT_TRUE(lhs - rhs == expected);
    }
}

TEST(TupleTests, NegateTest)
{
    {
        TupleF lhs{VectorF(0, 0, 0)};
        TupleF rhs{VectorF(1, -2, 3)};
        TupleF expected{VectorF(-1, 2, -3)};
        EXPECT_TRUE(lhs - rhs == expected);
    }
    {
        TupleF tup{1, -2, 3, -4};
        TupleF expected{-1, 2, -3, 4};
        EXPECT_TRUE(-tup == expected);
    }
}

TEST(TupleTests, MultiplyScalarTest)
{
    {
        TupleF tup{1, -2, 3, -4};
        TupleF expected{3.5, -7, 10.5, -14};
        float scalar{3.5f};
        EXPECT_TRUE(tup*scalar == expected);
        EXPECT_TRUE(scalar*tup == expected);

    }
    {
        TupleF tup{1, -2, 3, -4};
        TupleF expected{0.5, -1, 1.5, -2};
        float scalar{0.5f};
        EXPECT_TRUE(tup*scalar == expected);
        EXPECT_TRUE(scalar*tup == expected);
    }
}

TEST(TupleTests, DivideScalarTest)
{
    {
        TupleF tup{1, -2, 3, -4};
        TupleF expected{0.5, -1, 1.5, -2};
        float scalar{2};
        EXPECT_TRUE(tup/scalar == expected);
    }
    {
        TupleF tup{1, -2, 3, -4};
        float scalar{0};
        TupleF out{tup/scalar};
        EXPECT_TRUE(std::isinf(out.x));
        EXPECT_TRUE(std::isinf(out.y));
        EXPECT_TRUE(std::isinf(out.z));
        EXPECT_TRUE(std::isinf(out.w));
    }
}

TEST(TupleTests, MagnitudeTest)
{
    {
        TupleF tup{VectorF(1, 0, 0)};
        float expected{1};
        EXPECT_TRUE(tup.Magnitude() == expected);
        EXPECT_TRUE(Magnitude(tup) == expected);

    }
    {
        TupleF tup{VectorF(0, 1, 0)};
        float expected{1};
        EXPECT_TRUE(tup.Magnitude() == expected);
        EXPECT_TRUE(Magnitude(tup) == expected);
    }
    {
        TupleF tup{VectorF(0, 0, 1)};
        float expected{1};
        EXPECT_TRUE(tup.Magnitude() == expected);
        EXPECT_TRUE(Magnitude(tup) == expected);
    }
    {
        TupleF tup{VectorF(1, 2, 3)};
        float expected{std::sqrt(14.f)};
        EXPECT_TRUE(tup.Magnitude() == expected);
        EXPECT_TRUE(Magnitude(tup) == expected);
    }
    {
        TupleF tup{VectorF(-1, -2, -3)};
        float expected{std::sqrt(14.f)};
        EXPECT_TRUE(tup.Magnitude() == expected);
        EXPECT_TRUE(Magnitude(tup) == expected);
    }
}

TEST(TupleTests, NormalizeTest)
{
    {
        TupleF tup{VectorF(4, 0, 0)};
        TupleF expected{VectorF(1, 0, 0)};
        EXPECT_TRUE(tup.Normalize() == expected);
        EXPECT_TRUE(Normalize(tup) == expected);
    }
    {
        TupleF tup{VectorF(1, 2, 3)};
        TupleF expected{VectorF(0.26726, 0.53452, 0.80178)};
        EXPECT_TRUE(tup.Normalize() == expected);
        EXPECT_TRUE(Normalize(tup) == expected);
    }
    {
        TupleF tup{VectorF(1, 2, 3)};
        float expected{1.0f};
        EXPECT_TRUE(EQF(tup.Normalize().Magnitude(), expected));
        EXPECT_TRUE(EQF(Magnitude(Normalize(tup)), expected));
    }
}

TEST(TupleTests, CrossTest)
{
    {
        TupleF a{VectorF(1, 2, 3)};
        TupleF b{VectorF(2, 3, 4)};
        TupleF expected_axb{VectorF(-1, 2, -1)};
        TupleF expected_bxa{VectorF(1, -2, 1)};
        EXPECT_TRUE(a.Cross(b) == expected_axb);
        EXPECT_TRUE(Cross(a, b) == expected_axb);
        EXPECT_TRUE(b.Cross(a) == expected_bxa);
        EXPECT_TRUE(Cross(b, a) == expected_bxa);
    }
}

TEST(TupleTests, ColorTest)
{
    {
        Color color{-0.5, 0.4, 1.7};
        EXPECT_TRUE(EQF(color.red, -0.5));
        EXPECT_TRUE(EQF(color.green, 0.4));
        EXPECT_TRUE(EQF(color.blue, 1.7));
    }
}

TEST(TupleTests, ColorOperatorsTest)
{
    // +
    {
        Color color1{0.9, 0.6, 0.75};
        Color color2{0.7, 0.1, 0.25};
        Color expected{1.6, 0.7, 1.0};
        EXPECT_TRUE(color1+color2 == expected);
    }
    // -
    {
        Color color1{0.9, 0.6, 0.75};
        Color color2{0.7, 0.1, 0.25};
        Color expected{0.2, 0.5, 0.5};
        EXPECT_TRUE(color1-color2 == expected);
    }
    // *
    {
        Color color{0.2, 0.3, 0.4};
        float scalar{2.f};
        Color expected{0.4, 0.6, 0.8};
        EXPECT_TRUE(color*scalar == expected);
        EXPECT_TRUE(scalar*color == expected);
    }
}

TEST(TupleTests, ColorMultiplyTest)
{
    {
        Color color1{1, 0.2, 0.4};
        Color color2{0.9, 1, 0.1};
        Color expected{0.9, 0.2, 0.04};
        EXPECT_TRUE(color1*color2 == expected);
    }
}