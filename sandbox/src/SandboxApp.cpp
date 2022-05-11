#include <masterX.hpp>
#include <core/EntryPoint.hpp>

class SandboxLayer : public core::Layer
{
    virtual void onAttach() override
    {
        MX_APP_INFO("Hello Sandbox layer");
    }

    virtual void onDetach() override
    {
        MX_APP_INFO("Hello Sandbox layer leaving");
    }

    virtual bool onWindowClose(core::WindowCloseEvent& e) override
    {
        MX_APP_WARN("Are you trying to leave !!!");

        return true;
    }
};

class SandboxApp : public core::Application
{
public:
    SandboxApp()
    {
        MX_APP_INFO("Hello World");

        pushLayer(utils::Ref<SandboxLayer>(new SandboxLayer));
    }
};

core::Application* core::createApplication()
{
    return new SandboxApp;
}