#pragma once

#include <bitset>
#include <array>
#include <vector>
#include <list>

#include <rayplus/Vector2.hpp>
#include <rayplus/Color.hpp>

enum class DrawMode
{
    normal,
    rainbow,
    rainbow_porridge
};
constexpr auto draw_mode = DrawMode::normal;


constexpr double target_fps = 10;
constexpr auto frame_duration = std::chrono::duration<double>(1.0 / target_fps);
constexpr int rect_size = 5;
constexpr rayplus::Vector2<int> window_size = {1800, 900};
constexpr int X = window_size.x / rect_size;
constexpr int Y = window_size.y / rect_size;
constexpr int past_size = 1;
constexpr int howmh_frames_skip = 0;
constexpr int born_chance = 2;
constexpr auto shadow_color = rayplus::Color{0, 0, 0, 10};
const auto dead_color = rayplus::Color::black;


using Map = std::array<std::bitset<X + 2>, Y + 2>;
using Universe = std::array<Map, past_size + 1>;
using MapsInOrder = std::list<std::reference_wrapper<Map>>;
using Frame = std::pair<rayplus::Vector2<int>, rayplus::Vector2<int>>;

constexpr Frame full_frame = {
    {1, 1},
    {X, Y}
};

constexpr Frame little_frame = {
    {X / 2 - 10, Y / 2 - 10},
    {X / 2 + 10, Y / 2 + 10}
};

struct Config
{
public:
    Config()
    {
        set_drawing_only_present(true);
    }
    ~Config() = default;

    void set_drawing_only_present(bool is)
    {
        present_draw = is;
        alive_color = {230, 41, 55, 255 / (present_draw ? 1 : (past_size + 1))};
    }
    
    [[nodiscard]] bool is_drawing_only_present() const { return present_draw; }
    [[nodiscard]] rayplus::Color get_alive_color() const { return alive_color; }
    
private:
    bool present_draw = true;
    rayplus::Color alive_color = rayplus::Color::red;
} config;
