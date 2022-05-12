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

    virtual bool onWindowClose(WindowCloseEvent& e) override
    {
        MX_APP_WARN("Are you trying to leave !!!");

        return false;
    }

    virtual void onEventReceive(Event& e) override
    {
    }

    virtual void onImguiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello ImGui!");
        ImGui::End();
        bool open = true;
        ImGui::ShowDemoWindow(&open);
    }
};

class SandboxApp : public Application
{
public:
    SandboxApp()
    {
        MX_APP_INFO("Hello World");

        pushLayer(Ref<SandboxLayer>::Create());
    }
};

mx::Ref<mx::Application> mx::createApplication()
{
    return Ref<SandboxApp>::Create();
}