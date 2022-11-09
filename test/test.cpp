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

        mat_A.print();
    }

    tinyTools::matrix<int, 2, 3> mat_A{};

    template <typename T>
    void printArray(T const& array)
    {
        std::cout << "[ ";
        for( auto const a : array) { std::cout << a << ' '; }
        std::cout << "]\n";
    }

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
    auto const& array = mat.getData();
    printArray(array);
}

TEST_F(TestMatrix, Test_InitList_Ctor)
{
    tinyTools::matrix<int, 2, 3> mat_B { 0, 1, 2, 3, 4, 5 };
    compareArrays(mat_A.getData(), mat_B.getData());
}