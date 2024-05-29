#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "Color.h"

#include <iostream>
#include <format>


TEST(ColorTests, ColorTest)
{
    {
        Color color{-0.5, 0.4, 1.7};
        EXPECT_TRUE(EQF(color.red, -0.5));
        EXPECT_TRUE(EQF(color.green, 0.4));
        EXPECT_TRUE(EQF(color.blue, 1.7));
    }
}

TEST(ColorTests, ColorOperatorsTest)
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
    }
}

TEST(ColorTests, ColorMultiplyTest)
{
    {
        Color color1{1, 0.2, 0.4};
        Color color2{0.9, 1, 0.1};
        Color expected{0.9, 0.2, 0.04};
        EXPECT_TRUE(color1*color2 == expected);
    }
}