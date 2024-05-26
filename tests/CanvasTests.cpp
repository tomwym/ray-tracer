#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "GridLinearizer.h"
#include "Canvas.h"

#include <iostream>
#include <ranges>

TEST(CanvasTests, GridLinearizerTest)
{
    {
        // ****
        // ****
        // ****
        GridLinearizer cnvrt{3,4};
        EXPECT_TRUE(cnvrt.Get(0, 0) == 0);
        EXPECT_TRUE(cnvrt.Get(0) == (std::tuple{0,0}));
        EXPECT_TRUE(cnvrt.Get(0, 3) == 3);
        EXPECT_TRUE(cnvrt.Get(3) == (std::tuple{0,3}));
        EXPECT_TRUE(cnvrt.Get(1, 0) == 4);
        EXPECT_TRUE(cnvrt.Get(4) == (std::tuple{1,0}));
        EXPECT_TRUE(cnvrt.Get(1, 3) == 7);
        EXPECT_TRUE(cnvrt.Get(7) == (std::tuple{1,3}));
        EXPECT_TRUE(cnvrt.Get(2, 0) == 8);
        EXPECT_TRUE(cnvrt.Get(8) == (std::tuple{2,0}));
        EXPECT_TRUE(cnvrt.Get(2, 3) == 11);
        EXPECT_TRUE(cnvrt.Get(11) == (std::tuple{2,3}));
    }
    {
        // ***
        // ***
        // ***
        // ***
        GridLinearizer cnvrt{4,3};
        EXPECT_TRUE(cnvrt.Get(0, 0) == 0);
        EXPECT_TRUE(cnvrt.Get(0) == (std::tuple{0,0}));
        EXPECT_TRUE(cnvrt.Get(0, 2) == 2);
        EXPECT_TRUE(cnvrt.Get(2) == (std::tuple{0,2}));
        EXPECT_TRUE(cnvrt.Get(1, 0) == 3);
        EXPECT_TRUE(cnvrt.Get(3) == (std::tuple{1,0}));
        EXPECT_TRUE(cnvrt.Get(1, 2) == 5);
        EXPECT_TRUE(cnvrt.Get(5) == (std::tuple{1,2}));
        EXPECT_TRUE(cnvrt.Get(2, 0) == 6);
        EXPECT_TRUE(cnvrt.Get(6) == (std::tuple{2,0}));
        EXPECT_TRUE(cnvrt.Get(2, 2) == 8);
        EXPECT_TRUE(cnvrt.Get(8) == (std::tuple{2,2}));
        EXPECT_TRUE(cnvrt.Get(3, 0) == 9);
        EXPECT_TRUE(cnvrt.Get(9) == (std::tuple{3,0}));
        EXPECT_TRUE(cnvrt.Get(3, 2) == 11);
        EXPECT_TRUE(cnvrt.Get(11) == (std::tuple{3,2}));
    }
    {
        // ***
        // ***
        GridLinearizer cnvrt{2,3,1};
        EXPECT_TRUE(cnvrt.Get(1,1) == 0);
        EXPECT_TRUE(cnvrt.Get(0) == (std::tuple{1,1}));
        EXPECT_TRUE(cnvrt.Get(1,3) == 2);
        EXPECT_TRUE(cnvrt.Get(2) == (std::tuple{1,3}));
        EXPECT_TRUE(cnvrt.Get(2,1) == 3);
        EXPECT_TRUE(cnvrt.Get(3) == (std::tuple{2,1}));
        EXPECT_TRUE(cnvrt.Get(2,3) == 5);
        EXPECT_TRUE(cnvrt.Get(5) == (std::tuple{2,3}));
    }
    {
        // **
        // **
        // **
        GridLinearizer cnvrt{3,2,1};
        EXPECT_TRUE(cnvrt.Get(1,1) == 0);
        EXPECT_TRUE(cnvrt.Get(0) == (std::tuple{1,1}));
        EXPECT_TRUE(cnvrt.Get(1,2) == 1);
        EXPECT_TRUE(cnvrt.Get(1) == (std::tuple{1,2}));
        EXPECT_TRUE(cnvrt.Get(2,1) == 2);
        EXPECT_TRUE(cnvrt.Get(2) == (std::tuple{2,1}));
        EXPECT_TRUE(cnvrt.Get(2,2) == 3);
        EXPECT_TRUE(cnvrt.Get(3) == (std::tuple{2,2}));
        EXPECT_TRUE(cnvrt.Get(3,1) == 4);
        EXPECT_TRUE(cnvrt.Get(4) == (std::tuple{3,1}));
        EXPECT_TRUE(cnvrt.Get(3,2) == 5);
        EXPECT_TRUE(cnvrt.Get(5) == (std::tuple{3,2}));
    }
}

TEST(CanvasTests, CreationTest)
{
    {
        Canvas canvas{10, 20};
        EXPECT_EQ(canvas.width, 10);
        EXPECT_EQ(canvas.height, 20);
        Color black{0,0,0};
        for (int i=0; i<10; ++i) {
            for (int j=0; j<20; ++j) {
                EXPECT_EQ(canvas.PixelAt(i, j), black);
            }
        }
    }
}

TEST(CanvasTests, WritePixelTest)
{
    {
        Canvas canvas{10, 20};
        Color red{1,0,0};
        canvas.WritePixel(2,3, red);
        EXPECT_EQ(canvas.PixelAt(2,3), red);
    }
}

TEST(CanvasTests, PPMTest)
{
    {
        Canvas canvas{5,3};
        std::string ppm{canvas.PPMHeader()};
        std::string expected{"P3\n5 3\n255\n"};
        EXPECT_EQ(ppm, expected);
    }
    {
        Color c1{1.5, 0, 0};
        Color c2{0, 0.5, 0};
        Color c3{-0.5, 0, 1};
        Canvas canvas{5,3};

        canvas.WritePixel(0,0,c1);
        canvas.WritePixel(2,1,c2);
        canvas.WritePixel(4,2,c3);
        std::string ppm{canvas.PPMBody()};
        std::string expected{
R"lit(255 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 128 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 255
)lit"};
        EXPECT_EQ(ppm, expected);
    }
    {
        Canvas canvas{5,3, Color{1,0.8,0.6}};
        std::string ppm{canvas.PPMBody()};
        std::string expected{
R"lit(255 204 153 255 204 153 255 204 153 255 204 153 255 204 153
255 204 153 255 204 153 255 204 153 255 204 153 255 204 153
255 204 153 255 204 153 255 204 153 255 204 153 255 204 153
)lit"};
        EXPECT_EQ(ppm, expected);
    }
}
