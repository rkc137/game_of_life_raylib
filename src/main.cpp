#include <rayplus/Window.hpp>
#include <rayplus/Keyboard.hpp>

#include <random>
#include <thread>
#include <chrono>

#include "config.hpp"
#include "rules.hpp"

#include "draw.hpp"
#include "sim_frame.hpp"

void setup(Universe &maps, Frame frame)
{
    const auto [pos, size] = frame;
    for(auto &map : maps)
        for(int y = pos.y; y < size.y; y++)
        for(int x = pos.x; x < size.x; x++)
            map[y][x] = !(rand() % born_chance);
}

void clear(Universe &maps, Frame frame)
{
    const auto [pos, size] = frame;
    for(auto &map : maps)
        for(int y = pos.y; y < size.y; y++)
        for(int x = pos.x; x < size.x; x++)
            map[y][x] = false;
}

int main()
{
    Universe maps;
    MapsInOrder maps_in_order{maps.begin(), maps.end()};
    setup(maps, full_frame);

    auto win_closer = rayplus::window::init(
        window_size, "game of life raylib", target_fps
    );

    bool is_introverts = true;

    int rule_idx = 0;
    for(unsigned int turn = 0; !rayplus::window::should_close(); turn++)
    {
        auto start_time = std::chrono::system_clock::now();
        
        maps_in_order.splice(
            maps_in_order.end(),
            maps_in_order,
            maps_in_order.begin()
        );

        using namespace rayplus::keyboard;
        auto is_ctrl_down = (is_down(Key::left_control) || is_down(Key::right_control));
        switch(get_key_pressed())
        {
            case Key::enter:
                if(is_ctrl_down)
                {
                    is_introverts ^= true;
                    rule_idx = 0;
                } 
                else
                {
                    rule_idx = ++rule_idx % (is_introverts ? Rules::introverts.size() : Rules::extraverts.size());
                }
                rayplus::window::set_title(
                    std::string(is_introverts ? "introvert" : "extravert") + " rule: " + std::to_string(rule_idx));
            break;
            case Key::r:
                setup(maps, (is_ctrl_down ? little_frame : full_frame));
            break;
            case Key::c:
                clear(maps, (is_ctrl_down ? little_frame : full_frame));
            break;
            case Key::p:
                static bool idop = false;
                idop = !idop;
                config.set_drawing_only_present(idop);
            break;
            case Key::grave:
                config.draw_mode = static_cast<Config::DrawMode>(
                    (static_cast<int>(config.draw_mode) + 1) % Config::DrawModes_size
                );
            break;
            default:
        }

        if(is_introverts)
            sim_frame(maps_in_order, Rules::introverts[rule_idx]);
        else
            sim_frame(maps_in_order, Rules::extraverts[rule_idx]);

        if(!(turn % (howmh_frames_skip + 1)))
            draw(maps_in_order);

        std::this_thread::sleep_for(
            frame_duration - (std::chrono::system_clock::now() - start_time)
        );
    }

    return 0;
}