#include "gtest/gtest.h"
#include "../include/matrix.hpp"
#include <iostream>

class TestMatrix : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mat_A(0, 0) = 0;
        mat_A(0, 1) = 1;
        mat_A(0, 2) = 2;

        mat_A(1, 0) = 3;
        mat_A(1, 1) = 4;
        mat_A(1, 2) = 5;
    }

    tinyTools::matrix<int> mat_A{2, 3, 0};
};


// -----------------------------------------------------------------------------------------------------------------------------------------------------
// Ctors.
TEST_F(TestMatrix, Ctor_Reserve_Mem)
{
    tinyTools::matrix<int> mat { 2, 3 };
    EXPECT_EQ(mat.totalSize(), 6);    
}

TEST_F(TestMatrix, Ctor_Init_Val)
{
    tinyTools::matrix<int> mat { 2, 3, 7 };
    EXPECT_EQ(mat(0,0), 7);    
}

TEST_F(TestMatrix, Ctor_Init_Data)
{
    std::vector<int> data { 1, 2, 3, 4, 5, 6 };
    tinyTools::matrix<int> mat { 2, 3 , data };
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(0, 2), 3);
    EXPECT_EQ(mat(1, 0), 4);
    EXPECT_EQ(mat(1, 1), 5);
    EXPECT_EQ(mat(1, 2), 6);
}

TEST_F(TestMatrix, Ctor_Init_Move_Data)
{
    std::vector<int> data { 1, 2, 3, 4, 5, 6 };
    tinyTools::matrix<int> mat { 2, 3 , std::move(data) };
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(0, 2), 3);
    EXPECT_EQ(mat(1, 0), 4);
    EXPECT_EQ(mat(1, 1), 5);
    EXPECT_EQ(mat(1, 2), 6);
}

TEST_F(TestMatrix, Ctor_Init_List)
{
    tinyTools::matrix<int> mat { 2, 3 , { 1, 2, 3, 4, 5, 6 } };
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(0, 2), 3);
    EXPECT_EQ(mat(1, 0), 4);
    EXPECT_EQ(mat(1, 1), 5);
    EXPECT_EQ(mat(1, 2), 6);
}

TEST_F(TestMatrix, Ctor_Copy)
{
    tinyTools::matrix<int> mat { 2, 3 , { 1, 2, 3, 4, 5, 6 } };
    auto matCopy { mat };
    EXPECT_EQ(matCopy(0, 0), 1);
    EXPECT_EQ(matCopy(0, 1), 2);
    EXPECT_EQ(matCopy(0, 2), 3);
    EXPECT_EQ(matCopy(1, 0), 4);
    EXPECT_EQ(matCopy(1, 1), 5);
    EXPECT_EQ(matCopy(1, 2), 6); 
}

TEST_F(TestMatrix, Ctor_Move)
{
    tinyTools::matrix<int> mat { 2, 3 , { 1, 2, 3, 4, 5, 6 } };
    auto matCopy { std::move(mat) };
    EXPECT_EQ(matCopy(0, 0), 1);
    EXPECT_EQ(matCopy(0, 1), 2);
    EXPECT_EQ(matCopy(0, 2), 3);
    EXPECT_EQ(matCopy(1, 0), 4);
    EXPECT_EQ(matCopy(1, 1), 5);
    EXPECT_EQ(matCopy(1, 2), 6); 
}

TEST_F(TestMatrix, Ctor_Op)
{
    tinyTools::matrix<int> mat { 2, 3 , { 1, 2, 3, 4, 5, 6 } };
    tinyTools::matrix<int> matCopy{2, 3, 0};
    matCopy = mat;
    EXPECT_EQ(matCopy(0, 0), 1);
    EXPECT_EQ(matCopy(0, 1), 2);
    EXPECT_EQ(matCopy(0, 2), 3);
    EXPECT_EQ(matCopy(1, 0), 4);
    EXPECT_EQ(matCopy(1, 1), 5);
    EXPECT_EQ(matCopy(1, 2), 6); 
}

TEST_F(TestMatrix, Ctor_Op_Move)
{
    tinyTools::matrix<int> mat { 2, 3 , { 1, 2, 3, 4, 5, 6 } };
    tinyTools::matrix<int> matCopy{2, 3, 0};
    matCopy = std::move(mat);
    EXPECT_EQ(matCopy(0, 0), 1);
    EXPECT_EQ(matCopy(0, 1), 2);
    EXPECT_EQ(matCopy(0, 2), 3);
    EXPECT_EQ(matCopy(1, 0), 4);
    EXPECT_EQ(matCopy(1, 1), 5);
    EXPECT_EQ(matCopy(1, 2), 6); 
}