#include "Keyboard.hpp"

#include <raylib.h>

namespace raywrap::keyboard
{

bool is_pressed(Key key)
{
    return IsKeyReleased(static_cast<int>(key));
}

} // namespace raywrap