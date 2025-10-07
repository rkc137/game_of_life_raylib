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
constexpr int past_size = 3;
constexpr int howmh_frames_skip = 0;
constexpr int born_chance = 2;
constexpr bool is_rainbow_rave = true;
constexpr auto shadow_color = rayplus::Color{0, 0, 0, 10};
constexpr auto alive_color = rayplus::Color{230, 41, 55, 255 / (past_size + 1)};
const auto dead_color = rayplus::Color::black;

using Map = std::array<std::bitset<X + 2>, Y + 2>;
using PastMaps = std::vector<std::reference_wrapper<Map>>;
using Universe = std::array<Map, past_size + 1>;
using Frame = std::pair<rayplus::Vector2<int>, rayplus::Vector2<int>>;

constexpr Frame full_frame = {
    {1, 1},
    {X, Y}
};

constexpr Frame little_frame = {
    {X / 2 - 10, Y / 2 - 10},
    {X / 2 + 10, Y / 2 + 10}
};
