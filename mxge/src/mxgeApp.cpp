#include <masterX.hpp>
#include <core/EntryPoint.hpp>

#include "EditorLayer.hpp"

using namespace mx;

class MXGEApp : public Application
{
public:
    MXGEApp(const AppSettings& settings)
        : Application(settings)
    {
    }

    virtual void onInit() override
    {
        pushLayer(Ref<EditorLayer>::Create());
    }
};

Ref<Application> mx::createApplication(const CommandLineArgs& args)
{
    AppSettings settings;

    settings.args = args;

    settings.WinAPI = WindowAPI::GLFW;
    settings.GraphicsAPI = RendererAPI::OpenGL;

    settings.WinProperties.Title = "masterX Editor";
    settings.WinProperties.Width = 800;
    settings.WinProperties.Height = 600;
    settings.WinProperties.mode = mx::VideoMode::FullWindowed;

    return Ref<MXGEApp>::Create(settings);
}