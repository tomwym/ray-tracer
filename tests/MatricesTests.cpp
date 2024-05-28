#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

#include "Matrices.h"
#include "Constvals.h"

#include <iostream>

TEST(MatricesTests, IndexTest)
{
    {
        Matrix4f mat{{
            1.f,2.f,3.f,4.f,
            5.5f,6.5f,7.5f,8.5f,
            9.f,10.f,11.f,12.f,
            13.5f,14.5f,15.5f,16.5f
        }};
        EXPECT_EQ(mat(0,0), 1.f);
        EXPECT_EQ(mat(0,3), 4.f);
        EXPECT_EQ(mat(1,0), 5.5f);
        EXPECT_EQ(mat(1,2), 7.5f);
        EXPECT_EQ(mat(2,2), 11.f);
        EXPECT_EQ(mat(3,0), 13.5f);
        EXPECT_EQ(mat(3,2), 15.5f);
    }
    {
        Matrix2f mat{{
            -3.f,5.f,
            1.f,-2.f
        }};
        EXPECT_EQ(mat(0,0), -3.f);
        EXPECT_EQ(mat(0,1), 5.f);
        EXPECT_EQ(mat(1,0), 1.f);
        EXPECT_EQ(mat(1,1), -2.f);
    }
    {
        Matrix3f mat{{
            -3.f,5.f,0.f,
            1.f,-2.f,-7.f,
            0.f,1.f,1.f
        }};
        EXPECT_EQ(mat(0,0), -3.f);
        EXPECT_EQ(mat(1,1), -2.f);
        EXPECT_EQ(mat(2,2), 1.f);
    }
}

TEST(MatricesTests, EqualityTest)
{
    {
        Matrix4f matA{{
            1.f,2.f,3.f,4.f,
            5.f,6.f,7.f,8.f,
            9.f,8.f,7.f,6.f,
            5.f,4.f,3.f,2.f
        }};
        Matrix4f matB{{
            1.f,2.f,3.f,4.f,
            5.f,6.f,7.f,8.f,
            9.f,8.f,7.f,6.f,
            5.f,4.f,3.f,2.f
        }};
        EXPECT_TRUE(matA == matB);
        EXPECT_FALSE(matA != matB);
    }
    {
        Matrix2f matA{{
            1.f,2.f,
            3.f,4.f
        }};
        Matrix2f matB{{
            1.000009f,2.f,
            3.f,4.f
        }};
        EXPECT_TRUE(matA == matB);
        EXPECT_FALSE(matA != matB);
    }
    {
        Matrix2f matA{{
            1.f,2.f,
            3.f,4.f
        }};
        Matrix2f matB{{
            1.0001f,2.f,
            3.f,4.f
        }};
        EXPECT_FALSE(matA == matB);
        EXPECT_TRUE(matA != matB);
    }
}

TEST(MatricesTests, MultiplyMatrixTest)
{
    {
        Matrix4f matA{{
            1.f,2.f,3.f,4.f,
            5.f,6.f,7.f,8.f,
            9.f,8.f,7.f,6.f,
            5.f,4.f,3.f,2.f
        }};
        Matrix4f matB{{
            -2.f,1.f,2.f,3.f,
            3.f,2.f,1.f,-1.f,
            4.f,3.f,6.f,5.f,
            1.f,2.f,7.f,8.f
        }};
        Matrix4f expected{{
            20.f,22.f,50.f,48.f,
            44.f,54.f,114.f,108.f,
            40.f,58.f,110.f,102.f,
            16.f,26.f,46.f,42.f,
        }};
        EXPECT_TRUE(matA*matB == expected);
    }
}

TEST(MatricesTests, MultiplyVectorTest)
{
    {
        Matrix4f mat{{
            1.f,2.f,3.f,4.f,
            2.f,4.f,4.f,2.f,
            8.f,6.f,4.f,1.f,
            0.f,0.f,0.f,1.f
        }};
        Vector4f vec{{1.f,2.f,3.f,1.f}};
        Vector4f expected{{18.f,24.f,33.f,1.f}};
        EXPECT_TRUE(mat*vec == expected);
    }
}

TEST(MatricesTests, IdentityTest)
{
    {
        Matrix4f mat{{
            0.f,1.f,2.f,4.f,
            1.f,2.f,4.f,8.f,
            2.f,4.f,8.f,16.f,
            4.f,8.f,16.f,32.f
        }};
        Matrix4f id{Identity<float, 4>()};

        EXPECT_TRUE(mat*id == mat);
        EXPECT_TRUE(id*mat == mat);
    }
}

TEST(MatricesTests, TransposeTest)
{
    {
        Matrix4f mat{{
            0.f,9.f,3.f,0.f,
            9.f,8.f,0.f,8.f,
            1.f,8.f,5.f,3.f,
            0.f,0.f,5.f,8.f
        }};
        Matrix4f mat_transposed{{
            0.f,9.f,1.f,0.f,
            9.f,8.f,8.f,0.f,
            3.f,0.f,5.f,5.f,
            0.f,8.f,3.f,8.f
        }};
        EXPECT_TRUE(mat.Transpose() == mat_transposed);
        EXPECT_TRUE(mat_transposed.Transpose() == mat);
    }
}

TEST(MatricesTests, Determinant2x2Test)
{
    {
        Matrix2f mat{{
            1.f,5.f,-3.f,2.f
        }};
        float expected{17.f};
        EXPECT_TRUE(mat.Determinant() == expected);
    }
}

TEST(MatricesTests, SubMatrixTest)
{
    {
        Matrix3f mat{{
            1.f,5.f,0.f,
            -3.f,2.f,7.f,
            0.f,6.f,-3.f
        }};
        Matrix2f expected{{
            -3.f,2.f,0.f,6.f
        }};
        EXPECT_TRUE(mat.SubMatrix(0,2) == expected);
    }
    {
        Matrix4f mat{{
            -6.f,1.f,1.f,6.f,
            -8.f,5.f,8.f,6.f,
            -1.f,0.f,8.f,2.f,
            -7.f,1.f,-1.f,1.f
        }};
        Matrix3f expected{{
            -6.f,1.f,6.f,
            -8.f,8.f,6.f,
            -7.f,-1.f,1.f
        }};
        EXPECT_TRUE(mat.SubMatrix(2,1) == expected);
    }
}

TEST(MatricesTests, MinorTest)
{
    {
        Matrix3f mat{{
            3.f,5.f,0.f,
            2.f,-1.f,-7.f,
            6.f,-1.f,5.f
        }};
        float expected{25.f};
        Matrix2f sub{mat.SubMatrix(1,0)};
        EXPECT_TRUE(sub.Determinant() == expected);
        EXPECT_TRUE(mat.Minor(1,0) == 25.f);
    }
}

TEST(MatricesTests, CofactorTest)
{
    {
        Matrix3f mat{{
            3.f,5.f,0.f,
            2.f,-1.f,-7.f,
            6.f,-1.f,5.f
        }};
        EXPECT_TRUE(mat.Minor(0,0) == -12.f);
        EXPECT_TRUE(mat.Cofactor(0,0) == -12.f);
        EXPECT_TRUE(mat.Minor(1,0) == 25.f);
        EXPECT_TRUE(mat.Cofactor(1,0) == -25.f);
    }
}

TEST(MatricesTests, DeterminantTest)
{
    {
        Matrix3f mat{{
            1.f,2.f,6.f,
            -5.f,8.f,-4.f,
            2.f,6.f,4.f
        }};
        EXPECT_TRUE(mat.Cofactor(0,0) == 56.f);
        EXPECT_TRUE(mat.Cofactor(0,1) == 12.f);
        EXPECT_TRUE(mat.Cofactor(0,2) == -46.f);
        EXPECT_EQ(mat.Determinant(), -196.f);
    }
    {
        Matrix4f mat{{
            -2.f,-8.f,3.f,5.f,
            -3.f,1.f,7.f,3.f,
            1.f,2.f,-9.f,6.f,
            -6.f,7.f,7.f,-9.f,
        }};
        EXPECT_TRUE(mat.Cofactor(0,0) == 690.f);
        EXPECT_TRUE(mat.Cofactor(0,1) == 447.f);
        EXPECT_TRUE(mat.Cofactor(0,2) == 210.f);
        EXPECT_TRUE(mat.Cofactor(0,3) == 51.f);
        EXPECT_EQ(mat.Determinant(), -4071.f);
    }
}

TEST(MatricesTests, InvertibilityTest)
{
    {
        Matrix4f mat{{
            6.f,4.f,4.f,4.f,
            5.f,5.f,7.f,6.f,
            4.f,-9.f,3.f,-7.f,
            9.f,1.f,7.f,-6.f
        }};
        EXPECT_EQ(mat.Determinant(), -2120.f);
        EXPECT_TRUE(mat.Invertible());
    }
    {
        Matrix4f mat{{
            -4.f,2.f,-2.f,-3.f,
            9.f,6.f,2.f,6.f,
            0.f,-5.f,1.f,-5.f,
            0.f,0.f,0.f,0.f
        }};
        EXPECT_EQ(mat.Determinant(), -0.f);
        EXPECT_FALSE(mat.Invertible());
    }
}

TEST(MatricesTests, InverseTest)
{
    {
        Matrix4f mat{{
            -5.f, 2.f,6.f,-8.f,
            1.f,-5.f,1.f,8.f,
            7.f, 7.f,-6.f,-7.f,
            1.f,-3.f,7.f,4.f
        }};
        Matrix4f expected{{
            0.21805,0.45113,0.24060,-0.04511,
            -0.80827,-1.45677,-0.44361,0.52068,
            -0.07895,-0.22368,-0.05263,0.19737,
            -0.52256,-0.81391,-0.30075,0.30639
        }};
        ASSERT_TRUE(mat.Invertible());
        Matrix4f inverse(mat.Inverse());
        EXPECT_EQ(mat.Determinant(), 532.f);
        EXPECT_EQ(mat.Cofactor(2,3), -160.f);
        EXPECT_TRUE(EQF(inverse(3,2), -160.f/532.f));
        EXPECT_EQ(mat.Cofactor(3,2), 105.f);
        EXPECT_TRUE(EQF(inverse(2,3), 105.f/532.f));
        EXPECT_TRUE(inverse == expected);
    }
    {
        Matrix4f mat{{
            8.f,-5.f, 9.f,2.f,
            7.f,5.f, 6.f,1.f,
            -6.f,0.f, 9.f,6.f,
            -3.f,0.f,-9.f,-4.f
        }};
        Matrix4f expected{{
            -0.15385,-0.15385,-0.28205,-0.53846,
            -0.07692,0.12308,0.02564,0.03077,
            0.35897,0.35897,0.43590,0.92308,
            -0.69231,-0.69231,-0.76923,-1.92308
        }};
        EXPECT_TRUE(mat.Inverse() == expected);
    }
    {
        Matrix4f mat{{
            9.f,3.f,0.f,9.f,
            -5.f,-2.f,-6.f,-3.f,
            -4.f,9.f,6.f,4.f,
            -7.f,6.f,6.f,2.f
        }};
        Matrix4f expected{{
            -0.04074,-0.07778,0.14444,-0.22222,
            -0.07778,0.03333,0.36667,-0.33333,
            -0.02901,-0.14630,-0.10926,0.12963,
            0.17778,0.06667,-0.26667,0.33333
        }};
        EXPECT_TRUE(mat.Inverse() == expected);
    }
    {
        Matrix4f matA{{
            3.f,-9.f,7.f,3.f,
            3.f,-8.f,2.f,-9.f,
            -4.f,4.f,4.f,1.f,
            -6.f,5.f,-1.f,1.f
        }};
        Matrix4f matB{{
            8.f,2.f,2.f,2.f,
            3.f,-1.f,7.f,0.f,
            7.f,0.f,5.f,4.f,
            6.f,-2.f,0.f,5.f
        }};
        Matrix4f matC{matA*matB};
        EXPECT_TRUE(matC*matB.Inverse() == matA);
    }
}
