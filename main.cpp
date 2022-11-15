#include <iostream>
#include <chrono>
#include <thread>
#include "include/matrix.hpp"

static constexpr auto df_nTimes { 1'000 };

template <typename func_t>
void benchmark(func_t func)
{
    auto start = std::chrono::steady_clock::now();
    for(auto i{ 0 }; i < df_nTimes; ++i) { func(); }
    std::chrono::duration<double, std::milli> diff = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed = " << diff.count() << "ms.\n";
}

auto main() -> int
{
    return 0;
}