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
    static constexpr std::size_t rows { 1664 };
    static constexpr std::size_t cols { 936 };
    static constexpr std::size_t size { rows * cols * 2 };

    std::array<int, size> array{};

    // tinyTools::matrix<int, rows, cols> matA {};
    // tinyTools::matrix<int, rows, cols> matB {};

    /*benchmark( [&]()
    {
        matA.sum_scalar(1);
    } );

    benchmark( [&]()
    {
        matB.sum_scalar_par(1);
    } );

    std::cout << "--------------------------\n";
    benchmark( [&]()
    {
        matA.op_peq(1);
    } );

    benchmark( [&]()
    {
        matB.op_peq_par(1);
    } );

*/
    return array[0];
}