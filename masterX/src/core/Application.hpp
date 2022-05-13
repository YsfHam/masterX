#pragma once

#include "Window.hpp"
#include "LayerStack.hpp"
#include "Imgui/ImguiLayer.hpp"

namespace mx
{
    struct CommandLineArgs
    {
        uint32_t Argc;
        char **Argv;
    };

    struct AppSettings
    {
        WindowProps WinProperties;

        CommandLineArgs args;

        bool EnableImGui = true;
    };

    class Application : public EventsListener, public std::enable_shared_from_this<Application>
    {
    public:
        virtual ~Application();

        void pushLayer(mx::Ref<Layer> layer);
        void pushOverlay(mx::Ref<Layer> overlay);

        Window& getWindow() { return *m_window; }

        static Application& get() { return *s_instance; }

        const CommandLineArgs& getCommandLineArgs() { return m_cmdArgs; }


        void run();
    protected:
        Application(const AppSettings& settings = AppSettings());
    private:
        virtual void onEventReceive(Event& e) override;
        virtual bool onWindowClose(WindowCloseEvent& e) override;

    private:
        static Application *s_instance;

        std::unique_ptr<Window> m_window;
        Ref<ImguiLayer> m_imguiLayer;
        LayerStack m_layerStack;

        CommandLineArgs m_cmdArgs;
        bool m_imguiEnabled;
    }; 

    mx::Ref<mx::Application> createApplication(const CommandLineArgs& args);
}