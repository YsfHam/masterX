#include "mxpch.hpp"
#include "profiling.hpp"

namespace mx
{
    Statistics::StatisticsData Statistics::data;

    void Statistics::reset()
    {
        data.DrawCalls = 0;
    }
}