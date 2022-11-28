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

TEST_F(TestMatrix, Method_identity)
{
  tinyTools::matrix iden3 = tinyTools::matrix<int>::identity(3);

  std::vector<int> iden3_test = {1, 0, 0, 0, 1, 0, 0, 0, 1};

  compareVectors(iden3.getData(), iden3_test);
}

TEST_F(TestMatrix, Method_ones)
{
  tinyTools::matrix ones13 = tinyTools::matrix<int>::ones(1, 3);
  std::vector<int> ones13_test{1, 1, 1};
  compareVectors(ones13.getData(), ones13_test);

  tinyTools::matrix ones33 = tinyTools::matrix<int>::ones(3);
  std::vector<int> ones33_test{1, 1, 1, 1, 1, 1, 1, 1, 1};
  compareVectors(ones33.getData(), ones33_test);
}

TEST_F(TestMatrix, Method_zeros)
{
  tinyTools::matrix zeros13 = tinyTools::matrix<int>::zeros(1, 3);
  std::vector<int> zeros13_test{0, 0, 0};
  compareVectors(zeros13.getData(), zeros13_test);

  tinyTools::matrix zeros33 = tinyTools::matrix<int>::zeros(3);
  std::vector<int> zeros33_test{0, 0, 0, 0, 0, 0, 0, 0, 0};
  compareVectors(zeros33.getData(), zeros33_test);
}

TEST_F(TestMatrix, Method_random)
{
  std::srand(1); // Set seed for reproducibility.
  tinyTools::matrix random12 = tinyTools::matrix<int>::random(1, 2);
  std::vector<int> random12_test{1804289383, 846930886};
  compareVectors(random12.getData(), random12_test);

  tinyTools::matrix random22 = tinyTools::matrix<int>::random(2);
  std::vector<int> random22_test{1681692777, 1714636915, 1957747793, 424238335};
  compareVectors(random22.getData(), random22_test);

  tinyTools::matrix random_max = tinyTools::matrix<int>::random(1, 2, 5);
  std::vector<int> random_max_test{1, 2};
  compareVectors(random_max.getData(), random_max_test);

  std::srand(static_cast<unsigned int>(std::time(nullptr))); // Disable seed.
}

TEST_F(TestMatrix, Method_multiply_inplace)
{
  auto matA = tinyTools::matrix<int>{2, 2, {1, 2, 3, 4}};
  auto const matB = tinyTools::matrix<int>{2, 2, {5, 6, 7, 8}};

  auto const resolve = tinyTools::matrix<int>{2, 2, {5, 12, 21, 32}};

  matA.multiply(matB);
  compare2Matrixes(matA, resolve);
}

TEST_F(TestMatrix, Method_multiply)
{
  auto const matA = tinyTools::matrix<int>{2, 2, {1, 2, 3, 4}};
  auto const matB = tinyTools::matrix<int>{2, 2, {5, 6, 7, 8}};

  auto const resolve = tinyTools::matrix<int>{2, 2, {5, 12, 21, 32}};

  auto const matC = tinyTools::matrix<int>::multiply(matA, matB);
  compare2Matrixes(matC, resolve);
}

#endif /* METHODS_TEST_HPP */
