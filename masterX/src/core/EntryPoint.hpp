#pragma once

#include "Log.hpp"
#include "utils/types.hpp"
#include "core/AssetsManager.hpp"

extern mx::Ref<mx::Application> mx::createApplication(const CommandLineArgs& args);

int main(int argc, char **argv)
{
    mx::Log::init();
    MX_CORE_INFO("Engine starting ...");

    mx::Ref<mx::Application> app = mx::createApplication({(uint32_t)argc, argv});

    if (app != nullptr)
    {
        MX_CORE_INFO("Application created");
        app->run();
        app.reset();
        MX_CORE_INFO("Assets clearing...");
        mx::AssetsManager::clearAssets();
        MX_CORE_INFO("Assets cleared");
        MX_CORE_INFO("Application finish");
    }
    else
        MX_CORE_FATAL("Application creation failed");
    
    MX_CORE_INFO("Engine terminates");

    return 0;

}