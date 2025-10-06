#pragma once

#include <functional>

#include "config.hpp"

namespace Rules
{

using Extravert = const std::function<bool(int)>;
using Introvert = const std::function<bool(int, int)>;

const std::array<Extravert, 4> extraverts = {
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

const std::array<Introvert, 1> introverts = {
    [](int count, int selfs_count) -> bool {
        return (count == 3 || (count == 2 && selfs_count));
    }
};

}