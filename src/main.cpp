#include <raylib.h>

#include "raywrap/Window.hpp"

#include <bitset>
#include <array>
#include <random>
#include <thread>
#include <chrono>

constexpr int rect_size = 5;
constexpr int w_width = 1500;
constexpr int w_height = 1000;
constexpr int X = w_width / rect_size;
constexpr int Y = w_height / rect_size;
const auto delay = std::chrono::milliseconds(100); 
using Map = std::array<std::bitset<X + 2>, Y + 2>;

void draw(const Map &map)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
        for(int y = 0; y < Y; y++)
        for(int x = 0; x < X; x++)
            if(map[y + 1][x + 1])
                DrawRectangle(x * rect_size, y * rect_size, rect_size, rect_size, MAROON);
    EndDrawing();
}

void sim_frame(Map &past, Map &future)
{
    for(int y = 1; y < Y + 1; y++)
    for(int x = 1; x < X + 1; x++)
    {
        int count = -past[y][x];
        for(int i : {-1, 0, 1})
        for(int j : {-1, 0, 1})
            count += past[y + i][x + j];
        future[y][x] = (past[y][x] && count == 2) || count == 3;
    }
}

void setup(Map &map)
{
    for(int y = 1; y < Y + 1; y++)
    for(int x = 1; x < X + 1; x++)
        map[y][x] = !(rand() % 4);
}

int main()
{
    std::array<Map, 2> maps;
    setup(maps[0]);

    const double target_fps = 10;
    const std::chrono::duration<double> frame_duration(1.0 / target_fps);
    auto win_closer = raywrap::window::init(
        {w_width, w_height}, "game of life raylib", 10
    );
    
    for(bool turn = false; !raywrap::window::should_close(); turn = !turn)
    {
        auto start_time = std::chrono::system_clock::now();
        sim_frame(maps[turn], maps[!turn]);
        draw(maps[turn]);
        std::this_thread::sleep_for(frame_duration - (std::chrono::system_clock::now() - start_time));
    }

    return 0;
}