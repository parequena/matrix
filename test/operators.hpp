#ifndef OPERATORS_TEST_HPP
#define OPERATORS_TEST_HPP

#include "common.hpp"
TEST_F(TestMatrix, Op_parenthesis_const)
{
    float const value { 4.5F };
    tinyTools::matrix<float> const mat{1, 1, value};
    EXPECT_EQ(mat(0,0), value);
}

TEST_F(TestMatrix, Op_parenthesis)
{
    float const value { 4.5F };
    tinyTools::matrix<float> mat{1, 1, value};
    EXPECT_EQ(mat(0,0), value);
}

TEST_F(TestMatrix, Op_squareBracket_const)
{
    float const value { 4.5F };
    tinyTools::matrix<float> const mat{1, 1, value};
    EXPECT_EQ(mat[0], value);
}

TEST_F(TestMatrix, Op_squareBracket)
{
    float const value { 4.5F };
    tinyTools::matrix<float> mat{1, 1, value};
    EXPECT_EQ(mat[0], value);
}

TEST_F(TestMatrix, Op_equal)
{
    float const value { 4.5F };
    tinyTools::matrix<float> mat{1, 1, value};
    tinyTools::matrix<float> mat2{1, 1, value};
    EXPECT_TRUE(mat == mat2);
}

TEST_F(TestMatrix, Op_notEqual)
{
    float const value { 4.5F };
    tinyTools::matrix<float> mat{1, 1, value};
    tinyTools::matrix<float> mat2{1, 1, 6.7F};
    EXPECT_TRUE(mat != mat2);
}

TEST_F(TestMatrix, Op_minus)
{
    tinyTools::matrix<int> mat{1, 3, {0, 1, 2}};
    tinyTools::matrix<int> mat2{1, 3, {0, 2, 1}};
    auto result = mat < mat2;
    compareMatrix(result, {0, 1, 0});
}

TEST_F(TestMatrix, Op_minus_eq)
{
    tinyTools::matrix<int> mat{1, 3, {0, 1, 2}};
    tinyTools::matrix<int> mat2{1, 3, {0, 2, 1}};
    auto result = mat <= mat2;
    compareMatrix(result, {1, 1, 0});
}

TEST_F(TestMatrix, Op_greater)
{
    tinyTools::matrix<int> mat{1, 3, {0, 1, 2}};
    tinyTools::matrix<int> mat2{1, 3, {0, 2, 1}};
    auto result = mat > mat2;
    compareMatrix(result, {0, 0, 1});
}

TEST_F(TestMatrix, Op_greater_eq)
{
    tinyTools::matrix<int> mat{1, 3, {0, 1, 2}};
    tinyTools::matrix<int> mat2{1, 3, {0, 2, 1}};
    auto result = mat >= mat2;
    compareMatrix(result, {1, 0, 1});
}

TEST_F(TestMatrix, Op_plus_eq_mat)
{
    tinyTools::matrix<int> mat{1, 2, {0, 1}};
    tinyTools::matrix<int> mat2{1, 2, {0, 1}};
    mat += mat2;
    compareMatrix(mat, {0, 2});
}

TEST_F(TestMatrix, Op_plus_mat)
{
    tinyTools::matrix<int> mat{1, 2, {0, 1}};
    tinyTools::matrix<int> mat2{1, 2, {0, 1}};
    auto mat3 = mat += mat2;
    compareMatrix(mat3, {0, 2});
}

TEST_F(TestMatrix, Op_plus_eq_scalar)
{
    tinyTools::matrix<int> mat{1, 2, {0, 1}};
    mat += 1;
    compareMatrix(mat, {1, 2});
}

TEST_F(TestMatrix, Op_plus_scalar)
{
    tinyTools::matrix<int> mat{1, 2, {0, 1}};
    auto mat3 = mat += 1;
    compareMatrix(mat3, {1, 2});
}

TEST_F(TestMatrix, Op_minus_eq_mat)
{
    tinyTools::matrix<int> mat{1, 2, {0, 1}};
    tinyTools::matrix<int> mat2{1, 2, {0, 1}};
    mat -= mat2;
    compareMatrix(mat, {0, 0});
}

TEST_F(TestMatrix, Op_minus_mat)
{
    tinyTools::matrix<int> mat{1, 2, {0, 1}};
    tinyTools::matrix<int> mat2{1, 2, {0, 1}};
    auto mat3 = mat -= mat2;
    compareMatrix(mat3, {0, 0});
}

TEST_F(TestMatrix, Op_minus_eq_scalar)
{
    tinyTools::matrix<int> mat{1, 2, {0, 1}};
    mat -= 1;
    compareMatrix(mat, {-1, 0});
}

TEST_F(TestMatrix, Op_minus_scalar)
{
    tinyTools::matrix<int> mat{1, 2, {0, 1}};
    auto mat3 = mat -= 1;
    compareMatrix(mat3, {-1, 0});
}

TEST_F(TestMatrix, Op_multiply)
{
    tinyTools::matrix<int> matA{3, 3, {2, 0, 1, 3, 0, 0, 5, 1, 1}};
    tinyTools::matrix<int> matB{3, 3, {1, 0, 1, 1, 2, 1, 1, 1, 0}};
    tinyTools::matrix<int> res {3, 3, {3, 1, 2, 3, 0, 3, 7, 3, 6}};
    
    tinyTools::matrix<int> matC = matA * matB;
    compare2Matrixes(matC, res);
}



#endif /* OPERATORS_TEST_HPP */
