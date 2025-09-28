#pragma once

#include <functional>

#include "config.hpp"

std::array<std::function<bool(int)>, 3> rules = {
    [](int count) -> bool { 
        if(4 > count || count > 8)
            return false;
        // if(4 <= count || count <= 8)
        return true;
    },
    [](int count) -> bool { 
        if(4 > count || count > 8)
            return false;
        return true;
    }
};