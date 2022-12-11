# tinyTools::Matrix

Templatized Matrix library, not oprimized, and shurely you should use some good alternatives to use any matrixes\
    - [Dlib](http://dlib.net/linear_algebra.html#matrix)\
    - [Armadillo](https://arma.sourceforge.net/docs.html#Mat)\
    - [OpenCV](https://docs.opencv.org/4.x/d3/d63/classcv_1_1Mat.html)

And this library is just used to store all Matlab functions that I've been implementing all my life.
Also this library is mostly all the time done in [Twitch](www.twitch.tv/theApoCa) (In Spanish) and It's saved on [Youtube](https://www.youtube.com/watch?v=AVj6UfDKZpQ&list=PLBEviA0cKSihSTGFBgbKN1vLvSBUpp7qQ)

**Surely this interface can be changed, extended, or removed, and should not be used as better practices code.**

### Tecnologies

On this code I have been using some tecnologies just for fun:
- C++ 20
- Templates
- CMake
- clang-tidy (flags): `--checks=*,-llvm,-fuchisia*,-altera*,-llvmlibc-restrict-system-libc-headers -fix`
- clang-format
- All warnings enabled using [cpp_bestpractices](https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md) as reference.
- GTest

### Interface

``` cpp
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

    enum struct Direction : std::uint8_t
    {
        NONE,
        COLUMNS,
        ROWS
    };

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Ctors.
    inline explicit constexpr matrix(size_type const rows, size_type const cols);
    inline explicit constexpr matrix(size_type const rows, size_type const cols, T const& initialValue);
    inline explicit constexpr matrix(size_type const rows, size_type const cols, container_type const& data);
    inline constexpr matrix(size_type const rows, size_type const cols, std::initializer_list<value>&& data);
    inline explicit constexpr matrix(size_type const rows, size_type const cols, container_type&& data);
    inline constexpr matrix(matrix const& rhm);
    inline constexpr matrix(matrix&& rhm) noexcept;

    inline constexpr auto operator=(matrix const& rhm) -> matrix&;
    inline constexpr auto operator=(matrix&& rhm) noexcept -> matrix&;

    constexpr ~matrix() noexcept;

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Getters.
    [[nodiscard]] inline auto getData() const noexcept -> container_type;
    [[nodiscard]] inline constexpr auto rows() const noexcept -> size_type;
    [[nodiscard]] inline constexpr auto cols() const noexcept -> size_type;
    [[nodiscard]] inline constexpr auto totalSize() const noexcept -> size_type;

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Operators.
    template <numerical L_T>
    friend auto operator<<(std::ostream& os, matrix<L_T> const& rhm) -> std::ostream&;
    inline constexpr auto operator()(size_type r, size_type c) const -> const_reference;
    inline constexpr auto operator()(size_type r, size_type c) -> reference;

    inline constexpr auto operator()(size_type row, size_type col, size_type height, size_type width) const -> matrix;

    inline auto operator[](size_type idx) const -> const_reference;
    inline auto operator[](size_type idx) -> reference;

    inline constexpr auto operator==(matrix const& rhm) const noexcept -> bool;
    inline constexpr auto operator!=(matrix const& rhm) const noexcept -> bool;

    inline auto operator<(matrix const& rhm) const -> matrix<bool>;
    inline auto operator<=(matrix const& rhm) const -> matrix<bool>;

    inline auto operator>(matrix const& rhm) const -> matrix<bool>;
    inline auto operator>=(matrix const& rhm) const -> matrix<bool>;

    inline constexpr auto operator+=(matrix const& rhm) noexcept -> matrix&;
    friend constexpr auto operator+(matrix lhm, matrix const& rhm) noexcept -> matrix;

    inline constexpr auto operator+=(T const& scalar) noexcept -> matrix&;
    friend constexpr auto operator+(matrix lhm, T const& scalar) noexcept -> matrix;

    inline constexpr auto operator-=(matrix const& rhm) noexcept -> matrix&;
    friend constexpr auto operator-(matrix lhm, matrix const& rhm) noexcept -> matrix;

    inline constexpr auto operator-=(T const& scalar) noexcept -> matrix&;
    friend constexpr auto operator-(matrix lhm, T const& scalar) noexcept -> matrix;

    inline constexpr auto operator*(matrix const& rhm) const -> matrix;

    // -----------------------------------------------------------------------------------------------------------------------------------------------------
    // Methods.
    [[nodiscard]] inline static constexpr auto invalid() noexcept -> matrix;
    [[nodiscard]] inline constexpr auto sameSize(matrix const& rhm) const noexcept -> bool;
    [[nodiscard]] inline constexpr auto getRow(size_type const row) const -> matrix;
    [[nodiscard]] inline constexpr auto getCol(size_type const col) const -> matrix;

    [[nodiscard]] inline static constexpr auto identity(size_type const size) noexcept;

    [[nodiscard]] inline static constexpr auto ones(size_type size) noexcept -> matrix;
    [[nodiscard]] inline static constexpr auto ones(size_type rows, size_type cols) noexcept -> matrix;
    [[nodiscard]] inline static constexpr auto zeros(size_type size) noexcept -> matrix;
    [[nodiscard]] inline static constexpr auto zeros(size_type rows, size_type cols) noexcept -> matrix;
    [[nodiscard]] inline static constexpr auto random(size_type size) noexcept -> matrix;
    [[nodiscard]] inline static constexpr auto random(size_type rows, size_type cols) noexcept -> matrix;
    [[nodiscard]] inline static constexpr auto random(size_type rows, size_type cols, T max) noexcept -> matrix;

    // Multiply point by point. (Matlab: .*)
    inline constexpr auto multiply(matrix const& rhm) -> void;
    [[nodiscard]] inline static constexpr auto multiply(matrix const& lhm, matrix const& rhm) -> matrix;

    [[nodiscard]] inline constexpr auto sum(Direction dir) const -> matrix;
};
} // namespace tinyTools

#endif /* MATRIX_HPP */
```