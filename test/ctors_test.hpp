#ifndef CTORS_TEST_HPP
#define CTORS_TEST_HPP

#include "common.hpp"
TEST_F(TestMatrix, Ctor_Reserve_Mem)
{
  tinyTools::matrix<int> mat{2, 3};
  EXPECT_EQ(mat.totalSize(), 6);
}

TEST_F(TestMatrix, Ctor_Init_Val)
{
  tinyTools::matrix<int> mat{2, 3, 7};
  EXPECT_EQ(mat(0, 0), 7);
}

TEST_F(TestMatrix, Ctor_Init_Data)
{
  std::vector<int> data{1, 2, 3, 4, 5, 6};
  tinyTools::matrix<int> mat{2, 3, data};
  compareMatrix(mat, {1, 2, 3, 4, 5, 6});
}

TEST_F(TestMatrix, Ctor_Init_Move_Data)
{
  std::vector<int> data{1, 2, 3, 4, 5, 6};
  tinyTools::matrix<int> mat{2, 3, std::move(data)};
  compareMatrix(mat, {1, 2, 3, 4, 5, 6});
}

TEST_F(TestMatrix, Ctor_Init_List)
{
  tinyTools::matrix<int> mat{2, 3, {1, 2, 3, 4, 5, 6}};
  compareMatrix(mat, {1, 2, 3, 4, 5, 6});
}

TEST_F(TestMatrix, Ctor_Copy)
{
  tinyTools::matrix<int> mat{2, 3, {1, 2, 3, 4, 5, 6}};
  auto matCopy{mat};
  compareMatrix(mat, {1, 2, 3, 4, 5, 6});
}

TEST_F(TestMatrix, Ctor_Move)
{
  tinyTools::matrix<int> mat{2, 3, {1, 2, 3, 4, 5, 6}};
  auto matCopy{std::move(mat)};
  compareMatrix(matCopy, {1, 2, 3, 4, 5, 6});
}

TEST_F(TestMatrix, Ctor_Op)
{
  tinyTools::matrix<int> mat{2, 3, {1, 2, 3, 4, 5, 6}};
  tinyTools::matrix<int> matCopy{2, 3, 0};
  matCopy = mat;
  compareMatrix(matCopy, {1, 2, 3, 4, 5, 6});
}

TEST_F(TestMatrix, Ctor_Op_Move)
{
  tinyTools::matrix<int> mat{2, 3, {1, 2, 3, 4, 5, 6}};
  tinyTools::matrix<int> matCopy{2, 3, 0};
  matCopy = std::move(mat);
  compareMatrix(matCopy, {1, 2, 3, 4, 5, 6});
}


#endif /* CTORS_TEST_HPP */
