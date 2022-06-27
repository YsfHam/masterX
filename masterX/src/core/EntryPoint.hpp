#pragma once

#include "Log.hpp"
#include "utils/types.hpp"
#include "core/AssetsManager.hpp"
#include "utils/memory.hpp"

extern mx::Ref<mx::Application> mx::createApplication(const CommandLineArgs& args);

int main(int argc, char **argv)
{
    mx::MemTracker::init();
    
    mx::Log::init();
    MX_CORE_INFO("Engine starting ...");

    mx::Ref<mx::Application> app = mx::createApplication({(uint32_t)argc, argv});
    int exitCode = 0;
    if (app != nullptr)
    {
        app->onInit();
        MX_CORE_INFO("Application created");
        app->run();
        exitCode = app->getExitCode();
        app.reset();
        MX_CORE_INFO("Assets clearing...");
        mx::AssetsManager::clearAssets();
        MX_CORE_INFO("Assets cleared");
        MX_CORE_INFO("Application finish");
    }
    else
        MX_CORE_FATAL("Application creation failed");
    if (exitCode == 0)
        MX_CORE_INFO("Engine terminates");
    else
        MX_CORE_ERROR("Engine terminates with errors exit code {}", exitCode);

    mx::MemTracker::shutdown();

    return exitCode;

}