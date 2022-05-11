#include "mxpch.hpp"

#include "Log.hpp"

void core::Log::init() 
{
    addLogger("CORE");
    addLogger("APP");
}

std::shared_ptr<spdlog::logger> core::Log::addLogger(const std::string& name) 
{
    auto logger = spdlog::stdout_color_mt(name);
    logger->set_level(spdlog::level::trace);
    logger->set_pattern("%^[%T] [%n] [%l] %v%$");
    return logger;
}

std::shared_ptr<spdlog::logger> core::Log::getLogger(const std::string& name) 
{
    return spdlog::get(name);
}
