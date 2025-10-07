#pragma once

#include "rules.hpp"

template <typename RuleT>
void sim_frame(PastMaps &pasts, Map &future, RuleT &rule)
{
    for(int y = 1; y < Y + 1; y++)
    for(int x = 1; x < X + 1; x++)
    {
        int count = 0;
        int selfs_count = 0;
        for(auto past_ref : pasts)
        {
            auto &past = past_ref.get();
            count -= past[y][x];
            selfs_count += past[y][x];
            for(int i : {-1, 0, 1})
            for(int j : {-1, 0, 1})
                count += past[y + i][x + j];
        }

        if constexpr (std::is_same_v<RuleT, Rules::Extravert>)
            future[y][x] = rule(count);
        else if constexpr (std::is_same_v<RuleT, Rules::Introvert>)
            future[y][x] = rule(count, selfs_count);
        else static_assert(false, "the behavior for this rule (if its rule) is undefined");
    }
}