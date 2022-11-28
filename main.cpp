#include <iostream>
#include <chrono>
#include <thread>
#include "include/matrix.hpp"

static constexpr auto df_nTimes{1'000};

template <typename func_t> void benchmark(func_t func)
{
  auto start = std::chrono::steady_clock::now();
  for(auto i{0}; i < df_nTimes; ++i)
  {
    func();
  }
  std::chrono::duration<double, std::milli> diff = std::chrono::steady_clock::now() - start;
  std::cout << "Time elapsed = " << diff.count() << "ms.\n";
}

auto main() -> int
{
  // tinyTools::matrix<int> matA = tinyTools::matrix<int>::random(3, 3, 5);
  // tinyTools::matrix<int> matB = tinyTools::matrix<int>::random(3, 3, 6);

  auto const matA = tinyTools::matrix<int>{3, 2, {3, 4, 7, 2, 5, 9}};
  auto const matB = tinyTools::matrix<int>{2, 3, {3, 1, 5, 6, 9, 7}};

  auto C = matA * matB;

  return 0;
}