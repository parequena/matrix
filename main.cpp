#include <iostream>
#include <chrono>
#include <thread>
#include "include/matrix.hpp"

static constexpr auto df_nTimes{1'0};

template <typename func_t>
void benchmark(func_t func)
{
  auto start = std::chrono::steady_clock::now();
  for (auto i{0}; i < df_nTimes; ++i)
  {
    func();
  }
  std::chrono::duration<double, std::milli> diff = std::chrono::steady_clock::now() - start;
  std::cout << "Time elapsed = " << diff.count() << "ms.\n";
}

auto main() -> int
{
  auto const A = tinyTools::matrix<int>::random(1000);
  auto const B = tinyTools::matrix<int>::random(1000);

  benchmark(
      [&]() {
        auto const sumA_c = A.sum(tinyTools::matrix<int>::Direction::COLUMNS);
        auto const sumA_r = A.sum(tinyTools::matrix<int>::Direction::ROWS);
      });

  return 0;
}