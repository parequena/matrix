#ifndef COMMON_HPP
#define COMMON_HPP

#include "gtest/gtest.h"
#include "../include/matrix.hpp"

template <typename T> void compareVectors(std::vector<T> const& lhv, std::vector<T> const& rhv)
{
  EXPECT_EQ(lhv.size(), rhv.size());
  for(std::size_t i{}; i < rhv.size(); ++i)
  {
    EXPECT_EQ(lhv[ i ], rhv[ i ]);
  }
}

template <typename T> void compareMatrix(tinyTools::matrix<T> const& mat, std::vector<T> data) { compareVectors<T>(mat.data(), data); }

template <typename T> void compare2Matrixes(tinyTools::matrix<T> const& lhm, tinyTools::matrix<T> const& rhm) { compareVectors<T>(lhm.data(), rhm.data()); }


#endif /* COMMON_HPP */
