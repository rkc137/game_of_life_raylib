#pragma once

#include "config.hpp"

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
