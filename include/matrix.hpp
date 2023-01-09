#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <concepts>
#include <execution>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>

/* Nuestra:         Matlab:
       0 1 2          0 3 6
       3 4 5          1 4 7
       6 7 8          2 5 8
*/

namespace tinyTools
{
    template <typename T>
    concept numerical = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <numerical T>
    struct matrix
    {
        // -----------------------------------------------------------------------------------------------------------------------------------------------------
        using value = T;
        using reference = value &;
        using const_reference = value const &;
        using size_type = std::size_t;
        using container_type = std::vector<T>;

        enum struct Direction : std::uint8_t
        {
            NONE,
            COLUMNS,
            ROWS
        };

        // -----------------------------------------------------------------------------------------------------------------------------------------------------
        // Ctors.
        inline explicit constexpr matrix(size_type const rows, size_type const cols)
            : rows_{rows}, cols_{cols}, totalSize_{rows * cols}
        {
            if (rows == 0)
            {
                throw std::length_error("Rows can not be 0!\n");
            }
            if (cols == 0)
            {
                throw std::length_error("Cols can not be 0!\n");
            }
            data_.reserve(totalSize_);
        }

        inline explicit constexpr matrix(size_type const rows, size_type const cols, T const &initialValue)
            : matrix(rows, cols)
        {
            for (size_type i{}; i < totalSize(); ++i)
            {
                data_.emplace_back(initialValue);
            }
        }

        inline explicit constexpr matrix(size_type const rows, size_type const cols, container_type const &data)
            : rows_{rows}, cols_{cols}, totalSize_{rows * cols}, data_{data}
        {
            if (rows == 0)
            {
                throw std::length_error("Rows can not be 0!\n");
            }
            if (cols == 0)
            {
                throw std::length_error("Cols can not be 0!\n");
            }
        }

        inline constexpr matrix(size_type const rows, size_type const cols, std::initializer_list<value> &&data)
            : matrix(rows, cols, container_type{data})
        {
        }

        inline explicit constexpr matrix(size_type const rows, size_type const cols, container_type &&data)
            : matrix(rows, cols)
        {
            std::swap(data_, data);
        }

        inline constexpr matrix(matrix const &rhm)
            : matrix(rhm.rows(), rhm.cols_, rhm.data_)
        {
        }

        inline constexpr matrix(matrix &&rhm) noexcept
        {
            std::swap(rows_, rhm.rows_);
            std::swap(cols_, rhm.cols_);
            std::swap(totalSize_, rhm.totalSize_);
            std::swap(data_, rhm.data_);
        }

        inline constexpr auto operator=(matrix const &rhm) -> matrix & { return *this = matrix(rhm); }
        inline constexpr auto operator=(matrix &&rhm) noexcept -> matrix &
        {
            std::swap(rows_, rhm.rows_);
            std::swap(cols_, rhm.cols_);
            std::swap(totalSize_, rhm.totalSize_);
            std::swap(data_, rhm.data_);
            return *this;
        }

        constexpr ~matrix() noexcept
        {
            data_.clear();
        }

        // -----------------------------------------------------------------------------------------------------------------------------------------------------
        // Getters.
        [[nodiscard]] inline auto data() const noexcept -> container_type { return data_; }
        [[nodiscard]] inline constexpr auto rows() const noexcept -> size_type { return rows_; }
        [[nodiscard]] inline constexpr auto cols() const noexcept -> size_type { return cols_; }
        [[nodiscard]] inline constexpr auto totalSize() const noexcept -> size_type { return totalSize_; }

        // -----------------------------------------------------------------------------------------------------------------------------------------------------
        // Operators.
        template <numerical L_T>
        friend auto operator<<(std::ostream &os, matrix<L_T> const &rhm) -> std::ostream &;
        [[nodiscard]] inline constexpr auto operator()(size_type r, size_type c) const -> const_reference { return op_parenthesis(*this, r, c); }
        inline constexpr auto operator()(size_type r, size_type c) -> reference { return op_parenthesis(*this, r, c); }

        inline constexpr auto operator()(size_type row, size_type col, size_type height, size_type width) const -> matrix
        {
            if (row >= rows())
            {
                throw std::out_of_range(std::string{"Rows out of range, max rows= " + std::to_string(rows()) + '\n'});
            }
            if (col >= cols())
            {
                throw std::out_of_range(std::string{"Cols out of range, max cols= " + std::to_string(cols()) + '\n'});
            }

            auto const lastRow = row + height;
            auto const lastCol = col + width;

            if (lastRow > rows())
            {
                throw std::out_of_range("[HEIGHT] Max size out of bounds!\n");
            }
            if (lastCol > cols())
            {
                throw std::out_of_range(" [WIDHT] Max size out of bounds!\n");
            }

            matrix ret{height, width, 0};

            size_type i{}; // rows;
            for (size_type r{row}; r < lastRow; ++r)
            {
                size_type j{0}; // Cols.
                for (size_type c{col}; c < lastCol; ++c)
                {
                    ret(i, j) = op_parenthesis(*this, r, c);
                    ++j;
                }
                ++i;
            }

            return ret;
        }

        // Following matlab submatrix style: "(1:end, 1:3)"
        // inline constexpr auto operator()(std::string_view str) const -> matrix {}

        inline auto operator[](size_type idx) const -> const_reference { return op_sqBracket(*this, idx); }
        [[nodiscard]] inline auto operator[](size_type idx) -> reference { return op_sqBracket(*this, idx); }

        [[nodiscard]] inline constexpr auto operator==(matrix const &rhm) const noexcept -> bool
        {
            for (size_type i{}; i < totalSize(); ++i)
            {
                if (data_[i] != rhm.data_[i])
                {
                    return false;
                }
            }
            return true;
        }
        [[nodiscard]] inline constexpr auto operator!=(matrix const &rhm) const noexcept -> bool { return !(operator==(rhm)); }

        [[nodiscard]] inline auto operator<(matrix const &rhm) const -> matrix<bool>
        {
            if (!sameSize(rhm))
            {
                throw std::invalid_argument("Matrixes are not the same size!\n");
            }
            std::vector<bool> data{};
            data.reserve(totalSize());
            for (size_type i{}; i < totalSize(); ++i)
            {
                data.emplace_back(data_[i] < rhm.data_[i]);
            }
            return matrix<bool>{rows(), cols(), std::move(data)};
        }

        [[nodiscard]] inline auto operator<=(matrix const &rhm) const -> matrix<bool>
        {
            if (!sameSize(rhm))
            {
                throw std::invalid_argument("Matrixes are not the same size!\n");
            }
            std::vector<bool> data{};
            data.reserve(totalSize());
            for (size_type i{}; i < totalSize(); ++i)
            {
                data.emplace_back(data_[i] <= rhm.data_[i]);
            }
            return matrix<bool>{rows(), cols(), std::move(data)};
        }

        [[nodiscard]] inline auto operator>(matrix const &rhm) const -> matrix<bool>
        {
            if (!sameSize(rhm))
            {
                throw std::invalid_argument("Matrixes are not the same size!\n");
            }
            std::vector<bool> data{};
            data.reserve(totalSize());
            for (size_type i{}; i < totalSize(); ++i)
            {
                data.emplace_back(data_[i] > rhm.data_[i]);
            }
            return matrix<bool>{rows(), cols(), std::move(data)};
        }

        [[nodiscard]] inline auto operator>=(matrix const &rhm) const -> matrix<bool>
        {
            if (!sameSize(rhm))
            {
                throw std::invalid_argument("Matrixes are not the same size!\n");
            }
            std::vector<bool> data{};
            data.reserve(totalSize());
            for (size_type i{}; i < totalSize(); ++i)
            {
                data.emplace_back(data_[i] >= rhm.data_[i]);
            }
            return matrix<bool>{rows(), cols(), std::move(data)};
        }

        inline constexpr auto operator+=(matrix const &rhm) noexcept -> matrix &
        {
            for (size_type i{}; i < totalSize_; ++i)
            {
                data_[i] += rhm.data_[i];
            }
            return *this;
        }
        [[nodiscard]] friend constexpr auto operator+(matrix lhm, matrix const &rhm) noexcept -> matrix
        {
            lhm += rhm;
            return lhm;
        }

        inline constexpr auto operator+=(T const &scalar) noexcept -> matrix &
        {
            for (auto &d : data_)
            {
                d += scalar;
            }
            return *this;
        }
        [[nodiscard]] friend constexpr auto operator+(matrix lhm, T const &scalar) noexcept -> matrix
        {
            lhm += scalar;
            return lhm;
        }

        inline constexpr auto operator-=(matrix const &rhm) noexcept -> matrix &
        {
            for (size_type i{}; i < totalSize_; ++i)
            {
                data_[i] -= rhm.data_[i];
            }
            return *this;
        }
        [[nodiscard]] friend constexpr auto operator-(matrix lhm, matrix const &rhm) noexcept -> matrix
        {
            lhm -= rhm;
            return lhm;
        }

        inline constexpr auto operator-=(T const &scalar) noexcept -> matrix &
        {
            for (auto &d : data_)
            {
                d -= scalar;
            }
            return *this;
        }
        [[nodiscard]] friend constexpr auto operator-(matrix lhm, T const &scalar) noexcept -> matrix
        {
            lhm -= scalar;
            return lhm;
        }

        [[nodiscard]] inline constexpr auto operator*(matrix const &rhm) const -> matrix
        {
            if (cols() != rhm.rows())
            {
                throw std::invalid_argument("Matrixes left-matrix cols must be same size as right-matrix rows.\n");
            }
            matrix ret{rows(), rhm.cols(), 0};
            auto const totalSize = rows() * rhm.cols();

            for (size_type i{}; i < totalSize; ++i)
            {
                for (size_type r{}; r < cols(); ++r)
                {
                    ret[i] += op_parenthesis(*this, i / rows(), r) * rhm(r, i % rhm.cols());
                }
            }

            return ret;
        }

        // -----------------------------------------------------------------------------------------------------------------------------------------------------
        // Methods.
        [[nodiscard]] inline static constexpr auto invalid() noexcept -> matrix { return matrix{}; }
        [[nodiscard]] inline constexpr auto sameSize(matrix const &rhm) const noexcept -> bool { return (rows() == rhm.rows() && cols() == rhm.cols() && totalSize_ == rhm.totalSize()); }
        [[nodiscard]] inline constexpr auto getRow(size_type const row) const -> matrix
        {
            if (row >= rows())
            {
                throw std::out_of_range(std::string{"Rows out of range, max rows= " + std::to_string(rows()) + '\n'});
            }

            matrix ret{1, cols(), 0};
            for (size_type i{}; i < cols(); ++i)
            {
                ret[i] = op_parenthesis(*this, row, i);
            }
            return ret;
        }

        [[nodiscard]] inline constexpr auto getCol(size_type const col) const -> matrix
        {
            if (col >= cols())
            {
                throw std::out_of_range(std::string{"Cols out of range, max cols= " + std::to_string(cols()) + '\n'});
            }

            matrix ret{rows(), 1, 0};
            for (size_type i{}; i < rows(); ++i)
            {
                ret[i] = op_parenthesis(*this, i, col);
            }
            return ret;
        }

        [[nodiscard]] inline static constexpr auto identity(size_type const size) noexcept
        {
            matrix ret{size, size, 0};
            for (size_type i{}; i < size; ++i)
            {
                ret(i, i) = 1;
            }
            return ret;
        }

        [[nodiscard]] inline static constexpr auto ones(size_type size) noexcept -> matrix { return ones(size, size); }
        [[nodiscard]] inline static constexpr auto ones(size_type rows, size_type cols) noexcept -> matrix { return matrix{rows, cols, 1}; }
        [[nodiscard]] inline static constexpr auto zeros(size_type size) noexcept -> matrix { return zeros(size, size); }
        [[nodiscard]] inline static constexpr auto zeros(size_type rows, size_type cols) noexcept -> matrix { return matrix{rows, cols, 0}; }
        [[nodiscard]] inline static constexpr auto random(size_type size) noexcept -> matrix { return random(size, size); }
        [[nodiscard]] inline static constexpr auto random(size_type rows, size_type cols, T max = std::numeric_limits<T>::max()) noexcept -> matrix
        {
            matrix ret{rows, cols, 1};
            auto const totalSize = rows * cols;
            for (size_type i{}; i < totalSize; ++i)
            {
                ret[i] = static_cast<T>(std::rand()) % max;
            }
            return ret;
        }

        // Multiply point by point. (Matlab: .*)
        inline constexpr auto multiply(matrix const &rhm) -> void
        {
            if (!sameSize(rhm))
            {
                throw std::invalid_argument("Matrixes must have same size!");
            }
            for (size_type i{}; i < totalSize(); ++i)
            {
                data_[i] *= rhm[i];
            }
        }

        [[nodiscard]] inline static constexpr auto multiply(matrix const &lhm, matrix const &rhm) -> matrix
        {
            auto ret{lhm};
            ret.multiply(rhm);
            return ret;
        }

        [[nodiscard]] inline constexpr auto sum(Direction dir) const -> matrix
        {
            if (dir == Direction::NONE)
            {
                throw std::invalid_argument("Direction must be Columns (1) or Rows (2).\n");
            }

            if (dir == Direction::COLUMNS)
            {
                matrix ret{1, cols(), 0};
                for (size_type c{}; c < cols(); ++c)
                {
                    auto const &column = getCol(c).data();
                    ret(0, c) = std::accumulate(column.begin(), column.end(), 0);
                }
                return ret;
            }

            // Direction::ROWS.
            matrix ret{rows(), 1, 0};
            for (size_type r{}; r < rows(); ++r)
            {
                auto const &row = getRow(r).data();
                ret(r, 0) = std::accumulate(row.begin(), row.end(), 0);
            }
            return ret;
        }

        [[nodiscard]] static inline constexpr auto cat(Direction dir, matrix const &lhm, matrix const &rhm) -> matrix
        {
            // TODO: Not tested!
            auto const lh_r = lhm.rows();
            auto const lh_c = lhm.cols();

            auto const rh_r = rhm.rows();
            auto const rh_c = lhm.cols();

            if (dir == Direction::ROWS)
            {
                auto ret = matrix{lh_r + rh_r, lh_c};

                for (std::size_t c{}; c < lh_c; ++c)
                {                                        // For all columns.
                    for (std::size_t r{}; r < lh_r; ++r) // Copy all rows from left hand matrix.
                    {
                        ret(r, c) = lhm(r, c);
                    }

                    for (std::size_t r{}; r < rh_r; ++r) // Copy all rows from right hand matrix.
                    {
                        ret(r + lh_r, c) = rhm(r, c);
                    }
                }

                return ret;
            }
            else if (dir == Direction::COLUMNS)
            {
                auto ret = matrix{lh_r, lh_c + rh_c};

                for (std::size_t r{}; r < lh_r; ++r)
                {
                    for (std::size_t c{}; c < lh_c; ++c)
                        ret(r, c) = lhm(r, c);

                    for (std::size_t c{}; c < rh_c; ++c)
                        ret(r, c + lh_c) = rhm(r, c);
                }

                return ret;
            }
            else
            {
                std::cerr << "You can't provide NONE as Direction\n";
                return {};
            }
        }

        template <typename... args_t>
        [[nodiscard]] static inline constexpr auto cat(Direction dir, matrix const &lhm, matrix const &rhm, args_t &&...args) -> matrix
        {
            // TODO: Not tested!
            return cat(dir, cat(dir, lhm, rhm), std::forward<args_t>(args)...);
        }

    private:
        inline explicit constexpr matrix() noexcept = default;

        size_type rows_{};
        size_type cols_{};
        size_type totalSize_{rows_ * cols_};
        container_type data_{};

        // -----------------------------------------------------------------------------------------------------------------------------------------------------
        // Deducing This (C++20 Style). TODO: C++23
        template <typename This>
        [[nodiscard]] static inline auto op_parenthesis(This &instance, size_type r, size_type c) -> auto &
        {
            if (r >= instance.rows())
            {
                throw std::out_of_range(std::string{"Rows out of range, max rows= " + std::to_string(instance.rows()) + '\n'});
            }
            if (c >= instance.cols())
            {
                throw std::out_of_range(std::string{"Cols out of range, max cols= " + std::to_string(instance.cols()) + '\n'});
            }
            return instance.data_[r * instance.cols_ + c];
        }

        template <typename This>
        [[nodiscard]] static inline auto op_sqBracket(This &instance, size_type idx) -> auto &
        {
            if (idx >= instance.totalSize())
            {
                throw std::out_of_range(std::string{"Index out of range, max= " + std::to_string(instance.totalSize()) + '\n'});
            }
            return instance.data_[idx];
        }
    };

    template <numerical L_T>
    auto operator<<(std::ostream &os, matrix<L_T> const &rhm) -> std::ostream &
    {
        typename matrix<L_T>::size_type i{0};
        for (auto const d : rhm.data_)
        {
            os << d;
            if (++i == rhm.cols())
            {
                os << '\n';
                i = 0;
            }
            else
            {
                os << ' ';
            }
        }
        return os;
    }
} // namespace tinyTools

#endif /* MATRIX_HPP */