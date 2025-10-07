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

const std::array<Introvert, 2> introverts = {
    //classical
    [](int count, int selfs_count) -> bool {
        return (count == 3 || (count == 2 && selfs_count));
    },

    //interesting with (past_size == 3) 
    [](int count, int selfs_count) -> bool {
        if(count < 2 * past_size || 
           count > 3 * past_size)
            return false;
        if(count == 3 * past_size ||
           count == 3 * past_size - 1)
            return true;
        return selfs_count == 1;
    }
};

}