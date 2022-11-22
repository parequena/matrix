#ifndef METHODS_TEST_HPP
#define METHODS_TEST_HPP

#include "common.hpp"
TEST_F(TestMatrix, Method_same_size)
{
    tinyTools::matrix<int> mat{2, 3, 0};
    tinyTools::matrix<int> mat2{2, 3, 0};
    EXPECT_TRUE(mat.sameSize(mat2));
}

TEST_F(TestMatrix, Method_getRow)
{
    tinyTools::matrix<int> mat{2, 3, {1, 2, 3, 4, 5, 6}};
    
    auto const& row0 = mat.getRow(0);
    compareVectors(row0.getData(), {1, 2, 3});

    auto const& row1 = mat.getRow(1);
    compareVectors(row1.getData(), {4, 5, 6});
}

TEST_F(TestMatrix, Method_getCol)
{
    tinyTools::matrix<int> mat{2, 3, {1, 2, 3, 4, 5, 6}};
    
    auto const& col0 = mat.getCol(0);
    compareVectors(col0.getData(), {1, 4});
    
    auto const& col1 = mat.getCol(1);
    compareVectors(col1.getData(), {2, 5});
    
    auto const& col2 = mat.getCol(2);
    compareVectors(col2.getData(), {3, 6});
}

#endif /* METHODS_TEST_HPP */
