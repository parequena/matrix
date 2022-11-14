#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <concepts>
#include <array>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include <execution>

#include <cstdlib>

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
    using container_type = std::array<T, ROWS * COLS>;

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Ctors.
    inline constexpr explicit matrix() noexcept
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr))); // use current time as seed for random generator
        for(auto& d : data_)
        {
            d = std::rand();
        }
    }


    inline constexpr matrix(std::initializer_list<value>&& list)
    {
        if(list.size() != totalSize_) { throw std::out_of_range("Data passed must have same size as matrix."); }
        for(std::size_t i {}; auto const l : list) { data_[i] = l; ++i; }
    }

    inline constexpr matrix(container_type const& array) : data_{ array } { }
    inline constexpr matrix(container_type&& array) { std::swap(data_, array); }
    inline constexpr matrix(matrix const& rhm) : matrix( rhm.data_ ) { }
    inline constexpr matrix(matrix&& rhm) { std::swap(data_, rhm.data_); } 
    inline constexpr auto operator=(matrix const& rhm) -> matrix& { return *this = matrix(rhm); }
    inline constexpr auto operator=(matrix&& rhm) noexcept -> matrix& { std::swap(data_, rhm.data_); return *this; }

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Getters.
    inline auto getData() const noexcept -> std::array<T, ROWS * COLS> { return data_; }

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Operators.
    template <numerical L_T, std::size_t L_ROWS, std::size_t L_COLS>
    friend std::ostream& operator<<(std::ostream& os, matrix<L_T, L_ROWS, L_COLS> const& rhm);
    inline constexpr auto operator()(std::size_t r, std::size_t c) const -> const_reference { return op_parenthesis(*this, r, c); }
    inline constexpr auto operator()(std::size_t r, std::size_t c)       -> reference       { return op_parenthesis(*this, r, c); }

    inline constexpr auto operator[](std::size_t idx) const -> const_reference { return op_sqBracket(*this, idx); }
    inline constexpr auto operator[](std::size_t idx)       -> reference       { return op_sqBracket(*this, idx); }

    inline constexpr auto operator==(matrix const& rhm) const noexcept -> bool { for(std::size_t i{}; i < totalSize_; ++i) { if(data_[i] != rhm.data_[i]) { return false; } } return true; }
    inline constexpr auto operator!=(matrix const& rhm) const noexcept -> bool { return !(operator==(rhm)); }
    inline constexpr auto  operator<(matrix const& rhm) const noexcept -> matrix<bool, ROWS, COLS> { matrix<bool, ROWS, COLS> ret{}; for(std::size_t i{}; i < totalSize_; ++i) { ret[i] = data_[i]  < rhm.data_[i]; } return ret; }
    inline constexpr auto operator<=(matrix const& rhm) const noexcept -> matrix<bool, ROWS, COLS> { matrix<bool, ROWS, COLS> ret{}; for(std::size_t i{}; i < totalSize_; ++i) { ret[i] = data_[i] <= rhm.data_[i]; } return ret; }
    inline constexpr auto  operator>(matrix const& rhm) const noexcept -> matrix<bool, ROWS, COLS> { matrix<bool, ROWS, COLS> ret{}; for(std::size_t i{}; i < totalSize_; ++i) { ret[i] = data_[i]  > rhm.data_[i]; } return ret; }
    inline constexpr auto operator>=(matrix const& rhm) const noexcept -> matrix<bool, ROWS, COLS> { matrix<bool, ROWS, COLS> ret{}; for(std::size_t i{}; i < totalSize_; ++i) { ret[i] = data_[i] >= rhm.data_[i]; } return ret; }

    inline constexpr auto operator+=(matrix const& rhm) noexcept -> matrix& { for(std::size_t i{}; i < totalSize_; ++i) { data_[i] += rhm.data_[i]; } return *this; }
    friend constexpr auto operator+(matrix lhm, matrix const& rhm) noexcept -> matrix { lhm += rhm; return lhm; }
    inline constexpr auto operator+=(T const& scalar) noexcept -> matrix&   { for(auto& d : data_) { d += scalar; } return *this; }
    friend constexpr auto operator+(matrix lhm, T const& scalar) noexcept -> matrix { lhm += scalar; return lhm; }

    inline constexpr auto operator-=(matrix const& rhm) noexcept -> matrix& { for(std::size_t i{}; i < totalSize_; ++i) { data_[i] -= rhm.data_[i]; } return *this; }
    friend constexpr auto operator-(matrix lhm, matrix const& rhm) noexcept -> matrix { lhm -= rhm; return lhm; }
    inline constexpr auto operator-=(T const& scalar) noexcept -> matrix&   { for(auto& d : data_) { d -= scalar; } return *this; }
    friend constexpr auto operator-(matrix lhm, T const& scalar) noexcept -> matrix { lhm -= scalar; return lhm; }


    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Methods.
    inline constexpr void sum_scalar(T const& scalar) noexcept
    {
        for(auto& d : data_) { d += scalar; }
    }

    inline constexpr void sum_scalar_par(T const& scalar) noexcept
    {
        std::for_each(std::execution::unseq, data_.begin(), data_.end(), [&scalar](T& n) { n += scalar; });
    }

    inline constexpr auto op_peq(T const& scalar) noexcept -> matrix&
    {
        for(auto& d : data_) { d += scalar; }
        return *this;
    }
  
    inline constexpr auto op_peq_par(T const& scalar) noexcept -> matrix&
    {
        std::for_each(std::execution::par_unseq, data_.begin(), data_.end(),
        [&](T& d)
        {
            d += scalar;
        });

        return *this;
    }

private:
    static constexpr std::size_t totalSize_ { ROWS * COLS };
    container_type data_{};

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Deducing This (C++20 Style). TODO: C++23
    template<typename This>
    static inline constexpr auto op_parenthesis(This &instance, std::size_t r, std::size_t c) -> auto&
    {
        if(r >= ROWS) { throw std::out_of_range( std::string{ "Rows out of range, max rows= " + std::to_string(ROWS) + '\n' } ); }
        if(c >= COLS) { throw std::out_of_range( std::string{ "Cols out of range, max cols= " + std::to_string(COLS) + '\n' } ); }
        return instance.data_[r * COLS + c];
    }

    template<typename This>
    static inline constexpr auto op_sqBracket(This &instance, std::size_t idx) -> auto&
    {
        if(idx >= totalSize_) { throw std::out_of_range( std::string{ "Index out of range, max= " + std::to_string(totalSize_) + '\n' } ); }
        return instance.data_[idx];
    }
};

template <numerical L_T, std::size_t L_ROWS, std::size_t L_COLS>
std::ostream& operator<<(std::ostream& os, matrix<L_T, L_ROWS, L_COLS> const& rhm)
{
    std::size_t i { 0 };
    for(auto const d : rhm.data_)
    {
        os << d;
        if( ++i == L_COLS ) { os << '\n'; i = 0; }
        else                { os << ' '; }
    }
    return os;
}
} // namespace tinyTools

#endif /* MATRIX_HPP */