#pragma once

#include "mxpch.hpp"
#include "core/Timer.hpp"
#include "core/Log.hpp"

namespace mx
{
    class Statistics
    {
    public:
        struct StatisticsData
        {
            uint32_t DrawCalls = 0;
        };

    public:
        static void reset();

    public:
        static StatisticsData data;
    };

    class ScopeTimer
    {
    public:
        ScopeTimer(const std::string& scopeName)
            : m_scopeName(scopeName)
        {}
        ~ScopeTimer()
        {
            MX_CORE_WARN("Scope {}, ElapsedTime in miliseconds: {}", m_scopeName, m_timer.getElapsedTime().miliseconds());
        }
    private:
        Timer m_timer;

        std::string m_scopeName;
    };
}

#ifdef MX_DEBUG
    #define MX_TIMER_SCOPE(funcName) ScopeTimer timer_ ## funcName(#funcName)
#else
    #define MX_TIMER_SCOPE(funcName)
#endif