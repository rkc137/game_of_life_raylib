#pragma once

#include <functional>

#include "config.hpp"

using Rule = const std::function<bool(int)>;
const std::array<Rule, 3> rules = {
    [](int count) -> bool { 
        if(4 > count || count > 8)
            return false;
        // if(4 <= count || count <= 8)
        return true;
    },
    [](int count) -> bool { 
        return 4 > count && count > 8;
    },
    [](int count) -> bool { 
        return 4 > count || count > 8;
    }
};