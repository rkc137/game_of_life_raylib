#include <rayplus/Window.hpp>
#include <rayplus/Keyboard.hpp>
#include <rayplus/Logger.hpp>

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
    Universe maps{std::size_t(config.past_size_ref + 1), {}};
    MapsInOrder maps_in_order{maps.begin(), maps.end()};
    setup(maps, full_frame);

    auto win_closer = rayplus::window::init(
        window_size, "game of life raylib", target_fps
    );
    rayplus::logger::set_level(rayplus::logger::Level::none);

    bool is_introverts = true;

    int rule_idx = 0;
    auto update_title = [&](){
        rayplus::window::set_title(
            "past size: " + std::to_string(config.past_size_ref) +
            std::string(is_introverts ? "  introvert" : "  extravert") +
            " rule: " + std::to_string(rule_idx));
    };
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
                update_title();
            break;
            case Key::r:
                setup(maps, (is_ctrl_down ? little_frame : full_frame));
            break;
            case Key::c:
                clear(maps, (is_ctrl_down ? little_frame : full_frame));
            break;
            case Key::p:
                if(is_ctrl_down)
                {
                    static bool idop = false;
                    idop = !idop;
                    config.set_drawing_only_present(idop);   
                }
                else
                {
                    config.draw_mode = static_cast<Config::DrawMode>(
                        (static_cast<int>(config.draw_mode) + 1) % Config::DrawModes_size
                    );
                }
            break;
            case Key::grave:
            {
                //for now its just reassign
                int psize = config.past_size_ref;
                if(is_ctrl_down)
                {
                    if(psize <= 1)
                        break;
                    psize--;
                }
                else
                {
                    psize++;
                }
                config.set_past_size(psize);
                maps.resize(psize + 1);
                maps_in_order.assign(maps.begin(), maps.end());
                setup(maps, full_frame);
                update_title();
            }
            break;
            case Key::f11:
                rayplus::window::toggle_fullscreen();
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