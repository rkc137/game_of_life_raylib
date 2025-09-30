#include <rayplus/Window.hpp>
#include <rayplus/Draw.hpp>
#include <rayplus/Keyboard.hpp>

#include <random>
#include <thread>
#include <chrono>

#include "config.hpp"
#include "rules.hpp"

void draw(const Map &map)
{
    rayplus::draw([&](rayplus::DrawContext &ctx){
        ctx.clear(rayplus::black);
        for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
            if(map[y + 1][x + 1])
                ctx.draw_rect(
                    {rect_size * x, rect_size * y},
                    {rect_size,     rect_size},
                    rayplus::red
                );
    });
}

void sim_frame(PastMaps &pasts, Map &future, Rule &rule)
{
    for(int y = 1; y < Y + 1; y++)
    for(int x = 1; x < X + 1; x++)
    {
        int count = 0;
        for(auto past_ref : pasts)
        {
            auto &past = past_ref.get();
            count -= past[y][x];
            for(int i : {-1, 0, 1})
            for(int j : {-1, 0, 1})
                count += past[y + i][x + j];
        }

        //for now past of cell itself didnt have role
        future[y][x] = rule(count);
    }
}

void setup(Map &map)
{
    for(int y = frame_pos.y; y < frame_size.y; y++)
    for(int x = frame_pos.x; x < frame_size.x; x++)
        map[y][x] = !(rand() % 8);
}

int main()
{
    std::array<Map, past_size + 1> maps;
    for(auto &map : maps)
        setup(map);

    const double target_fps = 60;
    const std::chrono::duration<double> frame_duration(1.0 / target_fps);
    auto win_closer = rayplus::window::init(
        {w_width, w_height}, "game of life raylib", 10
    );

    int rule_idx = 0;
    for(unsigned int turn = 0; !rayplus::window::should_close(); turn++)
    {
        PastMaps pasts;
        pasts.reserve(past_size);
        for(int i = 0; i < past_size; i++)
            pasts.push_back(maps[(turn + i) % maps.size()]);
        auto &present = 
            maps[(turn + past_size) % maps.size()];
    

        using namespace rayplus::keyboard; 
        if(is_pressed(Key::ENTER))
        {
            rule_idx = ++rule_idx % rules.size();
            rayplus::window::set_title("rule: " + std::to_string(rule_idx));
        }
        else if(is_pressed(Key::SPACE))
            for(auto past : pasts)
                setup(past);     

        auto start_time = std::chrono::system_clock::now();
        sim_frame(pasts, present, rules[rule_idx]);
        if(!(turn % 10))
            draw(present);
        std::this_thread::sleep_for(
            frame_duration - (std::chrono::system_clock::now() - start_time)
        );
    }

    return 0;
}