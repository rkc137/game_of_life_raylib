#pragma once

#include <bitset>
#include <array>
#include <vector>

#include <rayplus/Vector2.hpp>
#include <rayplus/Color.hpp>

constexpr int rect_size = 5;
constexpr rayplus::Vector2<int> window_size = {1800, 900};
constexpr int X = window_size.x / rect_size;
constexpr int Y = window_size.y / rect_size;
constexpr int past_size = 2;
constexpr int howmh_frames_skip = 0;
constexpr int born_chance = 10;
const auto dead_color = rayplus::Color::white;
const auto alive_color = rayplus::Color{230, 41, 55, 255 / past_size};

constexpr rayplus::Vector2<int> frame_pos = {
    X / 2 - 10,
    Y / 2 - 10
};
constexpr rayplus::Vector2<int> frame_size = {
    X / 2 + 10,
    Y / 2 + 10
};

using Map = std::array<std::bitset<X + 2>, Y + 2>;
using PastMaps = std::vector<std::reference_wrapper<Map>>;
using Universe = std::array<Map, past_size + 1>;
