#pragma once

#include <bitset>
#include <array>
#include <vector>
#include <list>

#include <rayplus/Vector2.hpp>
#include <rayplus/Color.hpp>


constexpr double target_fps = 10;
constexpr auto frame_duration = std::chrono::duration<double>(1.0 / target_fps);
constexpr int rect_size = 5;
constexpr rayplus::Vector2<int> window_size = {1800, 900};
constexpr int X = window_size.x / rect_size;
constexpr int Y = window_size.y / rect_size;
constexpr int howmh_frames_skip = 0;
constexpr int born_chance = 2;
constexpr auto shadow_color = rayplus::Color{0, 0, 0, 10};
const auto dead_color = rayplus::Color::black;

using Map = std::array<std::bitset<X + 2>, Y + 2>;
using Universe = std::vector<Map>;
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

    
    enum class DrawMode
    {
        normal = 0,
        rainbow,
        rainbow_porridge,
        enum_size
    } draw_mode = DrawMode::normal;
    static constexpr int DrawModes_size = static_cast<int>(DrawMode::enum_size);

    int past_size = 1;
private:
    bool present_draw = true;
    rayplus::Color alive_color = rayplus::Color::red;
} config;
