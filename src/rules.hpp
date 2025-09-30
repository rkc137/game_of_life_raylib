#pragma once

#include <functional>

#include "config.hpp"

using Rule = const std::function<bool(int)>;
const std::array<Rule, 3> rules = {
    [](int count) -> bool { 
        if(2 * past_size > count || count > 4 * past_size)
            return false;
        return true;
    },
    [](int count) -> bool { 
        return 2 * past_size > count && count > 4 * past_size;
    },
    [](int count) -> bool { 
        return 2 * past_size > count || count > 4 * past_size;
    }
};