#include <masterX.hpp>
#include <core/EntryPoint.hpp>

using namespace mx;

class SandboxLayer : public Layer
{
    virtual void onAttach() override
    {
        MX_APP_INFO("Hello Sandbox layer");
    }

    virtual void onDetach() override
    {
        MX_APP_INFO("Hello Sandbox layer leaving");
    }

    virtual void onUpdate() override
    {
        if (Input::isKeyPressedOnce(Key::R))
        {
            MX_APP_INFO("Key R is pressed");
        }
    }

    virtual bool onWindowClose(WindowCloseEvent& e) override
    {
        MX_APP_WARN("Are you trying to leave !!!");

        return false;
    }

    virtual bool onKeyPressed(KeyPressedEvent& e) override
    {

        return true;
    }

    virtual void onEventReceive(Event& e) override
    {
    }

    virtual void onImguiRender() override
    {
    }
};

class SandboxApp : public Application
{
public:
    SandboxApp(const AppSettings& settings)
        : Application(settings)
    {
        MX_APP_INFO("Hello World");

        pushLayer(Ref<SandboxLayer>::Create());
    }
};

mx::Ref<mx::Application> mx::createApplication(const CommandLineArgs& args)
{
    AppSettings settings;
    settings.WinProperties.Title = "Sandbox App";
    return Ref<SandboxApp>::Create(settings);
}