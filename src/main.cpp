#include <rayplus/Window.hpp>
#include <rayplus/Draw.hpp>
#include <rayplus/Keyboard.hpp>

#include <random>
#include <thread>
#include <chrono>

#include "config.hpp"
#include "rules.hpp"

void draw(const Universe &maps)
{
    rayplus::draw([&](rayplus::DrawContext &ctx){
        rayplus::Color rainbow_color;
        if constexpr (draw_mode == DrawMode::normal)
        {
            ctx.clear(dead_color);
        }
        else
        {
            //you cant make shadow with clear, cause when clean calls, its CLEAR it all
            ctx.draw_rect({}, window_size, shadow_color);
            
            if constexpr (draw_mode == DrawMode::rainbow)
                rainbow_color = rayplus::Color{rand() % 255, rand() % 255, rand() % 255, 255};
            // else if constexpr (draw_mode == DrawMode::rainbow_porridge);
        }
        
        for(auto &map : maps)
        {
            for(int y = 0; y < Y; y++)
            for(int x = 0; x < X; x++)
                if(map[y + 1][x + 1])
                    ctx.draw_rect(
                        {rect_size * x, rect_size * y},
                        {rect_size,     rect_size},
                        [&]() -> rayplus::Color {
                            if constexpr (draw_mode == DrawMode::normal)
                                return alive_color;
                            else if constexpr (draw_mode == DrawMode::rainbow)
                                return rainbow_color;
                            else if constexpr (draw_mode == DrawMode::rainbow_porridge)
                                return {rand() % 255, rand() % 255, rand() % 255, 255};
                            else
                                throw std::runtime_error("the behavior for this rule (if its rule) is undefined");
                            return {};
                        }()
                    );
        }
    });
}

template <typename RuleT>
void sim_frame(PastMaps &pasts, Map &future, RuleT &rule)
{
    for(int y = 1; y < Y + 1; y++)
    for(int x = 1; x < X + 1; x++)
    {
        int count = 0;
        int selfs_count = 0;
        for(auto past_ref : pasts)
        {
            auto &past = past_ref.get();
            count -= past[y][x];
            selfs_count += past[y][x];
            for(int i : {-1, 0, 1})
            for(int j : {-1, 0, 1})
                count += past[y + i][x + j];
        }

        if constexpr (std::is_same_v<RuleT, Rules::Extravert>)
            future[y][x] = rule(count);
        else if constexpr (std::is_same_v<RuleT, Rules::Introvert>)
            future[y][x] = rule(count, selfs_count);
        else static_assert(false, "the behavior for this rule (if its rule) is undefined");
    }
}

void setup(Map &map)
{
    static const auto [pos, size] = full_frame;
    for(int y = pos.y; y < size.y; y++)
    for(int x = pos.x; x < size.x; x++)
        map[y][x] = !(rand() % born_chance);
}

int main()
{
    Universe maps;
    for(auto &map : maps)
        setup(map);

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
        else if(is_pressed(Key::space))
            for(auto past : pasts)
                setup(past);

        sim_frame(pasts, present, current_rules[rule_idx]);
        if(!(turn % (howmh_frames_skip + 1)))
            draw(maps);
        std::this_thread::sleep_for(
            frame_duration - (std::chrono::system_clock::now() - start_time)
        );
    }

    return 0;
}