#pragma once

#include <bitset>
#include <array>

constexpr int rect_size = 5;
constexpr int w_width = 1800;
constexpr int w_height = 900;
constexpr int X = w_width / rect_size;
constexpr int Y = w_height / rect_size;
constexpr int past_size = 2;
using Map = std::array<std::bitset<X + 2>, Y + 2>;
using PastMaps = std::array<std::reference_wrapper<Map>, past_size>;
