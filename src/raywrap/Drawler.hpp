#pragma once

#include "Vector2.hpp"

namespace raywrap
{

struct DrawContext
{
    void draw_rect(Vector2<int> pos, Vector2<int> size);
    void clear();
};

class Drawler
{
public:
    inline static DrawContext ctx;
    Drawler();
    ~Drawler();
};

}