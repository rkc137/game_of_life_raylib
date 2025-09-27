#pragma once

#include <type_traits>

namespace raywrap
{

template <typename T>
requires (std::is_arithmetic_v<T>)
struct Vector2
{
    T x, y;
};

} // namespace raywrap