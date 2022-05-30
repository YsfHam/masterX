#pragma once

#include "mxpch.hpp"
#include "utils/types.hpp"

namespace mx
{
    class Log
    {
    public:
        static void init();

        static Ref<spdlog::logger> addLogger(const std::string& name);
        static Ref<spdlog::logger> getLogger(const std::string& name);
    };
}

#define MX_LOG_TRACE(logger, ...) ::mx::Log::getLogger(logger)->trace(__VA_ARGS__)
#define MX_LOG_INFO(logger, ...)  ::mx::Log::getLogger(logger)->info(__VA_ARGS__)
#define MX_LOG_WARN(logger, ...)  ::mx::Log::getLogger(logger)->warn(__VA_ARGS__)
#define MX_LOG_ERROR(logger, ...) ::mx::Log::getLogger(logger)->error(__VA_ARGS__)
#define MX_LOG_FATAL(logger, ...) ::mx::Log::getLogger(logger)->critical(__VA_ARGS__)

#define MX_CORE_TRACE(...) MX_LOG_TRACE("CORE", __VA_ARGS__)
#define MX_CORE_INFO(...)  MX_LOG_INFO("CORE", __VA_ARGS__)
#define MX_CORE_WARN(...)  MX_LOG_WARN("CORE", __VA_ARGS__)
#define MX_CORE_ERROR(...) MX_LOG_ERROR("CORE", __VA_ARGS__)
#define MX_CORE_FATAL(...) MX_LOG_FATAL("CORE", __VA_ARGS__)

#define MX_TRACE(...) MX_LOG_TRACE("APP", __VA_ARGS__)
#define MX_INFO(...)  MX_LOG_INFO("APP", __VA_ARGS__)
#define MX_WARN(...)  MX_LOG_WARN("APP", __VA_ARGS__)
#define MX_ERROR(...) MX_LOG_ERROR("APP", __VA_ARGS__)
#define MX_FATAL(...) MX_LOG_FATAL("APP", __VA_ARGS__)