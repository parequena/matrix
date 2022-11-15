#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <concepts>
#include <vector>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include <execution>

#include <cstdlib>

namespace tinyTools
{
template <typename T>
concept numerical = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <numerical T>
struct matrix
{
    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    using value = T;
    using reference = value&;
    using const_reference = value const&;
    using size_type = std::size_t;
    using container_type = std::vector<T>;

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Ctors.
    inline explicit constexpr matrix(size_type const rows, size_type const cols) noexcept 
        : rows_{ rows }
        , cols_{ cols }
        , totalSize_{ rows_ * cols_ }
    {
        data_.reserve(totalSize_);
    }

    inline explicit constexpr matrix(size_type const rows, size_type const cols, T const& initialValue)
        : rows_{ rows }
        , cols_{ cols }
        , totalSize_{ rows_ * cols_ }
    {
        data_.reserve(totalSize_);
        for (size_type i{}; i < totalSize_; ++i) { data_.emplace_back(initialValue); }
    }

    inline explicit constexpr matrix(size_type const rows, size_type const cols, container_type const& data)
        : rows_{ rows }
        , cols_{ cols }
        , totalSize_{ rows_ * cols_ }
        , data_{ data }
    { }

    inline constexpr matrix(size_type const rows, size_type const cols, std::initializer_list<value>&& data)
        : matrix(rows, cols, container_type{data})
    { }

    inline explicit constexpr matrix(size_type const rows, size_type const cols, container_type&& data)
        : matrix(rows, cols)
    {
        std::swap(data_, data);
    }

    inline explicit constexpr matrix(matrix const& rhm)
        : matrix( rhm.rows_, rhm.cols_, rhm.data_ )
    { }

    inline constexpr matrix(matrix&& rhm)
    {
        std::swap(rows_, rhm.rows_);
        std::swap(cols_, rhm.cols_);
        std::swap(totalSize_, rhm.totalSize_);
        std::swap(data_, rhm.data_);
    }

    inline constexpr auto operator=(matrix const& rhm) -> matrix& { return *this = matrix(rhm); }
    inline constexpr auto operator=(matrix&& rhm) noexcept -> matrix&
    {
        std::swap(rows_, rhm.rows_);
        std::swap(cols_, rhm.cols_);
        std::swap(totalSize_, rhm.totalSize_);
        std::swap(data_, rhm.data_);
        return *this;
    }

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Getters.
    inline auto getData() const noexcept -> container_type { return data_; }
    inline constexpr size_type rows() const noexcept { return rows_; }
    inline constexpr size_type cols() const noexcept { return cols_; }
    inline constexpr size_type totalSize() const noexcept { return totalSize_; }
    inline constexpr bool sameSize(matrix const& rhm) const noexcept { return (rows_ == rhm.rows_ && cols_ == rhm.cols_ && totalSize_ == rhm.totalSize_)    ; }

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Operators.
    template <numerical L_T>
    friend std::ostream& operator<<(std::ostream& os, matrix<L_T> const& rhm);
    inline constexpr auto operator()(size_type r, size_type c) const -> const_reference { return op_parenthesis(*this, r, c); }
    inline constexpr auto operator()(size_type r, size_type c)       -> reference       { return op_parenthesis(*this, r, c); }

    inline auto operator[](size_type idx) const -> const_reference { return op_sqBracket(*this, idx); }
    inline auto operator[](size_type idx)       -> reference       { return op_sqBracket(*this, idx); }

    inline constexpr auto operator==(matrix const& rhm) const noexcept -> bool { for(size_type i{}; i < totalSize_; ++i) { if(data_[i] != rhm.data_[i]) { return false; } } return true; }
    inline constexpr auto operator!=(matrix const& rhm) const noexcept -> bool { return !(operator==(rhm)); }
    
    inline auto operator<(matrix const& rhm) const -> matrix<bool>
    {
        if(!sameSize(rhm)) { throw std::invalid_argument("Matrixes are not the same size!\n"); }
        matrix<bool> ret{rows_, cols_, 0};
        for (size_type i{}; i < totalSize_; ++i) { ret[i] = generic_operator(data_[i], rhm.data_[i], operator<()); }
        return ret;
    }
    
    inline auto operator<=(matrix const& rhm) const -> matrix<bool>
    {
        if(!sameSize(rhm)) { throw std::invalid_argument("Matrixes are not the same size!\n"); }
        matrix<bool> ret{rows_, cols_, 0};
        for (size_type i{}; i < totalSize_; ++i) { ret[i] = generic_operator(data_[i], rhm.data_[i], operator<=()); }
        return ret;
    }

    inline auto operator>(matrix const& rhm) const -> matrix<bool>
    {
        if(!sameSize(rhm)) { throw std::invalid_argument("Matrixes are not the same size!\n"); }
        matrix<bool> ret{rows_, cols_, 0};
        for (size_type i{}; i < totalSize_; ++i) { ret[i] = generic_operator(data_[i], rhm.data_[i], operator>()); }
        return ret;
    }

    inline auto operator>=(matrix const& rhm) const -> matrix<bool>
    {
        if(!sameSize(rhm)) { throw std::invalid_argument("Matrixes are not the same size!\n"); }
        matrix<bool> ret{rows_, cols_, 0};
        for (size_type i{}; i < totalSize_; ++i) { ret[i] = generic_operator(data_[i], rhm.data_[i], operator>=()); }
        return ret;
    }

    inline constexpr auto operator+=(matrix const& rhm) noexcept -> matrix& { for(size_type i{}; i < totalSize_; ++i) { data_[i] += rhm.data_[i]; } return *this; }
    friend constexpr auto operator+(matrix lhm, matrix const& rhm) noexcept -> matrix { lhm += rhm; return lhm; }
    inline constexpr auto operator+=(T const& scalar) noexcept -> matrix&   { for(auto& d : data_) { d += scalar; } return *this; }
    friend constexpr auto operator+(matrix lhm, T const& scalar) noexcept -> matrix { lhm += scalar; return lhm; }

    inline constexpr auto operator-=(matrix const& rhm) noexcept -> matrix& { for(size_type i{}; i < totalSize_; ++i) { data_[i] -= rhm.data_[i]; } return *this; }
    friend constexpr auto operator-(matrix lhm, matrix const& rhm) noexcept -> matrix { lhm -= rhm; return lhm; }
    inline constexpr auto operator-=(T const& scalar) noexcept -> matrix&   { for(auto& d : data_) { d -= scalar; } return *this; }
    friend constexpr auto operator-(matrix lhm, T const& scalar) noexcept -> matrix { lhm -= scalar; return lhm; }


    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Methods.
    static auto invalid() noexcept -> matrix { return matrix{}; }

private:
    inline explicit constexpr matrix() noexcept = default;
    
    size_type rows_{};
    size_type cols_{};
    size_type totalSize_ { rows_ * cols_ };
    container_type data_{};

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Deducing This (C++20 Style). TODO: C++23
    template<typename This>
    static inline auto op_parenthesis(This &instance, size_type r, size_type c) -> auto&
    {
        if(r >= instance.rows_) { throw std::out_of_range( std::string{ "Rows out of range, max rows= " + std::to_string(instance.rows_) + '\n' } ); }
        if(c >= instance.cols_) { throw std::out_of_range( std::string{ "Cols out of range, max cols= " + std::to_string(instance.cols_) + '\n' } ); }
        return instance.data_[r * instance.cols_ + c];
    }

    template<typename This>
    static inline auto op_sqBracket(This &instance, size_type idx) -> auto&
    {
        if(idx >= instance.totalSize_) { throw std::out_of_range( std::string{ "Index out of range, max= " + std::to_string(instance.totalSize_) + '\n' } ); }
        return instance.data_[idx];
    }

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Generic operator to use all other operators.
    template <class func_t>
    inline constexpr bool generic_operator(T const& lhd, T const& rhd, [[maybe_unused]] func_t func) const noexcept { return lhd.func(rhd); }
};

template <numerical L_T>
std::ostream& operator<<(std::ostream& os, matrix<L_T> const& rhm)
{
    typename matrix<L_T>::size_type i { 0 };
    for(auto const d : rhm.data_)
    {
        os << d;
        if( ++i == rhm.cols_ ) { os << '\n'; i = 0; }
        else                   { os << ' '; }
    }
    return os;
}
} // namespace tinyTools

#endif /* MATRIX_HPP */