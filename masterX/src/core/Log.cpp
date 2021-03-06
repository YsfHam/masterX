#include "mxpch.hpp"

#include "Log.hpp"

void mx::Log::init() 
{
    addLogger("CORE");
    addLogger("APP");
}

mx::Ref<spdlog::logger> mx::Log::addLogger(const std::string& name) 
{
    auto logger = spdlog::stdout_color_mt(name);
    logger->set_level(spdlog::level::trace);
    logger->set_pattern("%^[%T] [%n] [%l] %v%$");
    return logger;
}

mx::Ref<spdlog::logger> mx::Log::getLogger(const std::string& name) 
{
    return spdlog::get(name);
}
