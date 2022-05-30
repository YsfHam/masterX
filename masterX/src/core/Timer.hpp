#pragma once

#include "Time.hpp"
#include <chrono>

namespace mx
{
    class Timer
    {
    public:
        Timer();

        Time getElapsedTime() const;
        Time restart();


    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_time;
    };
};