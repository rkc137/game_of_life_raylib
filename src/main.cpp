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
    static const auto [pos, size] = frame;
    for(auto &map : maps)
        for(int y = pos.y; y < size.y; y++)
        for(int x = pos.x; x < size.x; x++)
            map[y][x] = !(rand() % born_chance);
}

void clear(Universe &maps, Frame frame)
{
    static const auto [pos, size] = frame;
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

    static auto &current_rules = Rules::introverts;
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
        switch(get_key_pressed())
        {
            case Key::enter:
                rule_idx = ++rule_idx % current_rules.size();
                rayplus::window::set_title("rule: " + std::to_string(rule_idx));
            break;
            case Key::r:
                setup(maps, full_frame);
            break;
            case Key::space:
                setup(maps, little_frame);
            break;
            case Key::c:
                clear(maps, little_frame);
            break;
            default:
        }

        sim_frame(maps_in_order, current_rules[rule_idx]);
        if(!(turn % (howmh_frames_skip + 1)))
            draw(maps_in_order);
        std::this_thread::sleep_for(
            frame_duration - (std::chrono::system_clock::now() - start_time)
        );
    }

    return 0;
}