#pragma once

#include "Drawler.hpp"

#include <type_traits>
#include <utility>

namespace raywrap
{

template <typename T>
void draw(T&& func)
{
    Drawler drawler;
    func(Drawler::ctx);
}
    
}