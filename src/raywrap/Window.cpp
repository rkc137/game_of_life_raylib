#include "Window.hpp"

#include <raylib.h>

namespace raywrap::window
{

WindowCloser::~WindowCloser()
{
    if(is_closed) return;
    is_closed = true;
    CloseWindow();
}

WindowCloser init(Vector2<int> size, std::string title, int target_fps)
{
    window_size = size;
    InitWindow(window_size.x, window_size.y, title.c_str());
    SetTargetFPS(target_fps);
    return WindowCloser{};
}

bool should_close()
{
    return WindowShouldClose();
}

void set_title(std::string title)
{
    SetWindowTitle(title.c_str());
}

} // namespace raywrap::window