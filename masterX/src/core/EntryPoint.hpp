#pragma once

#include "Log.hpp"
#include "utils/types.hpp"

extern core::Application* core::createApplication();

int main(int argc, char **argv)
{
    core::Log::init();
    MX_CORE_INFO("Engine starting ...");

    utils::Ref<core::Application> app = utils::Ref<core::Application>(core::createApplication());

    if (app != nullptr)
    {
        MX_CORE_INFO("Application created");
        app->run();
        app.reset();
        MX_CORE_INFO("Application finish");
    }
    else
        MX_CORE_FATAL("Application creation failed");

    MX_CORE_INFO("Engine terminates");

    return 0;

}