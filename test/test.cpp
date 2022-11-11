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

    tinyTools::matrix<int, 2, 3> mat_A{};

    template <typename T>
    void compareArrays(T const& lha, T const& rha)
    {
        std::size_t const ls = lha.size();
        std::size_t const rs = rha.size();

        EXPECT_EQ(ls, rs);
        for(std::size_t i{}; i < ls; ++i)
        {
            EXPECT_EQ(lha[i], rha[i]);
        }
    }
};


TEST_F(TestMatrix, DumpyTest)
{
    tinyTools::matrix<int, 2, 3> mat{};
    mat(0, 0) = 3;
    [[maybe_unused]] auto const& array = mat.getData();
}

TEST_F(TestMatrix, Test_InitList_Ctor)
{
    tinyTools::matrix<int, 2, 3> mat_B { 0, 1, 2, 3, 4, 5 };
    EXPECT_TRUE(mat_A == mat_B);
}

TEST_F(TestMatrix, Test_Array_Ctor)
{
    constexpr std::size_t cols { 2 };
    constexpr std::size_t rows { 3 };
    std::array<int, rows * cols> data{ 0, 1, 2, 3, 4, 5 };
    tinyTools::matrix<int, rows, cols> mat{ std::move(data) };
}