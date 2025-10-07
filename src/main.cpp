#include <rayplus/Window.hpp>
#include <rayplus/Draw.hpp>
#include <rayplus/Keyboard.hpp>

#include <random>
#include <thread>
#include <chrono>

#include "config.hpp"
#include "rules.hpp"

#include "draw.hpp"
#include "sim_frame.hpp"

void setup(Map &map, Frame frame)
{
    static const auto [pos, size] = frame;
    for(int y = pos.y; y < size.y; y++)
    for(int x = pos.x; x < size.x; x++)
        map[y][x] = !(rand() % born_chance);
}

int main()
{
    Universe maps;
    for(auto &map : maps)
        setup(map, full_frame);

    const double target_fps = 60;
    const std::chrono::duration<double> frame_duration(1.0 / target_fps);
    auto win_closer = rayplus::window::init(
        window_size, "game of life raylib", 10
    );

    int rule_idx = 0;
    for(unsigned int turn = 0; !rayplus::window::should_close(); turn++)
    {
        auto start_time = std::chrono::system_clock::now();
        PastMaps pasts;
        pasts.reserve(past_size);
        for(int i = 0; i < past_size; i++)
            pasts.push_back(maps[(turn + i) % maps.size()]);
        auto &present = 
            maps[(turn + past_size) % maps.size()];
    

        using namespace rayplus::keyboard; 
        static auto &current_rules = Rules::introverts;
        if(is_pressed(Key::enter))
        {
            rule_idx = ++rule_idx % current_rules.size();
            rayplus::window::set_title("rule: " + std::to_string(rule_idx));
        }
        else if(is_pressed(Key::r))
            for(auto past : pasts)
                setup(past, full_frame);
        else if(is_pressed(Key::space))
            for(auto past : pasts)
                setup(past, little_frame);

        sim_frame(pasts, present, current_rules[rule_idx]);
        if(!(turn % (howmh_frames_skip + 1)))
            draw(maps);
        std::this_thread::sleep_for(
            frame_duration - (std::chrono::system_clock::now() - start_time)
        );
    }

    return 0;
}