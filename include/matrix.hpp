#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <concepts>
#include <array>
#include <stdexcept>
#include <initializer_list>

namespace tinyTools
{
template <typename T>
concept numerical = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <numerical T, std::size_t ROWS, std::size_t COLS>
struct matrix
{
    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    using value = T;
    using reference = value&;
    using const_reference = value const&;

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Ctors.
    inline constexpr explicit matrix() noexcept = default;
    inline constexpr matrix(std::initializer_list<value>&& list)
    {
        if(list.size() != totalSize_) { throw std::out_of_range("Data passed must have same size as matrix."); }
        for(std::size_t i {}; auto const l : list) { data_[i] = l; ++i; }
    }

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Getters.
    inline auto getData() const noexcept -> std::array<T, ROWS * COLS> { return data_; }

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Operators.
    inline constexpr auto operator()(std::size_t r, std::size_t c) const -> const_reference { return op_parenthesis(*this, r, c); }
    inline constexpr auto operator()(std::size_t r, std::size_t c)       -> reference       { return op_parenthesis(*this, r, c); }

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Methods.
    void print() const noexcept
    {
        std::size_t i { 0 };
        for(auto const d : data_)
        {
            std::cout << d;
            if( ++i == COLS ) { std::cout << '\n'; i = 0; }
            else              { std::cout << ' '; }
        }
    }
    
private:
    static constexpr std::size_t totalSize_ { ROWS * COLS };
    std::array<T, totalSize_> data_{};

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Deducing This (C++20 Style). TODO: C++23
    template<typename This>
    static inline constexpr auto op_parenthesis(This &instance, std::size_t r, std::size_t c) -> auto&
    {
        if(r > ROWS) { throw std::out_of_range( std::string{ "Rows out of range, max rows= " + std::to_string(ROWS) + '\n' } ); }
        if(c > COLS) { throw std::out_of_range( std::string{ "Cols out of range, max cols= " + std::to_string(COLS) + '\n' } ); }
        return instance.data_[r * COLS + c];
    }
};


} // namespace tinyTools

#endif /* MATRIX_HPP */