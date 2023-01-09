#ifndef GETTERS_TEST_HPP
#define GETTERS_TEST_HPP

#include "common.hpp"
TEST_F(TestMatrix, Get_Data)
{
  std::vector<char> data{'P', 'a', 'b', 'l', 'o'};
  tinyTools::matrix<char> mat(1, 5, data);
  auto const &priv_data = mat.data();
  compareVectors(data, priv_data);
}

TEST_F(TestMatrix, Get_Rows)
{
  tinyTools::matrix<char> mat(1, 5, {'P', 'a', 'b', 'l', 'o'});
  EXPECT_EQ(mat.rows(), 1);
}

TEST_F(TestMatrix, Get_Cols)
{
  tinyTools::matrix<char> mat(1, 5, {'P', 'a', 'b', 'l', 'o'});
  EXPECT_EQ(mat.cols(), 5);
}

TEST_F(TestMatrix, Get_TotalSize)
{
  tinyTools::matrix<char> mat(1, 5, {'P', 'a', 'b', 'l', 'o'});
  EXPECT_EQ(mat.totalSize(), 5);
}

TEST_F(TestMatrix, Get_Size)
{
  tinyTools::matrix<char> mat(1, 5, {'P', 'a', 'b', 'l', 'o'});
  auto const [r, c] = tinyTools::size(mat);

  EXPECT_EQ(r, 1);
  EXPECT_EQ(c, 5);
}

#endif /* GETTERS_TEST_HPP */
