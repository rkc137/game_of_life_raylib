#pragma once

#include <string>

#include "Vector2.hpp"

namespace raywrap::window
{

class WindowCloser
{
public:
    WindowCloser() = default;
    ~WindowCloser();
private:
    inline static bool is_closed = false;
};

static Vector2<int> window_size = {};
WindowCloser init(Vector2<int> size, std::string title, int target_fps = 60);
bool should_close();

} // namespace raywrap::window