#pragma once

#include "mxpch.hpp"

namespace mx
{
    class Statistics
    {
    public:
        struct StatisticsData
        {
            uint32_t DrawCalls = 0;
        };

        static StatisticsData data;
    };
}