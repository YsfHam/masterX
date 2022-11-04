#pragma once

#include "Window.hpp"
#include "LayerStack.hpp"
#include "Imgui/ImguiLayer.hpp"
#include "utils/types.hpp"
#include "Renderer/GraphicsContext.hpp"

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
        WindowAPI WinAPI = WindowAPI::None;

        RendererAPI GraphicsAPI;

        CommandLineArgs args;

        bool EnableImGui = true;
    };

    class Application : public EventsListener, public std::enable_shared_from_this<Application>
    {
    public:
        virtual ~Application();

        void pushLayer(mx::Ref<Layer> layer);
        void pushOverlay(mx::Ref<Layer> overlay);

        Window& getWindow();

        static Application& get() { return *s_instance; }

        const CommandLineArgs& getCommandLineArgs() { return m_cmdArgs; }
        WindowAPI getWindowAPI() const { return m_windowAPI; }
        RendererAPI getRendererAPI() const { return m_rendererAPI; }
        void exit(int32_t exitCode = 0)
        {
            m_exitCode = exitCode;
            m_running = false;
        }

        void setImGuiEventsBlocking(bool blockEvents);

        int32_t getExitCode() const { return m_exitCode; }

        virtual void onInit() = 0;


        void run();
    protected:
        Application(const AppSettings& settings = AppSettings());
    private:
        virtual void onEventReceive(Event& e) override;
        virtual bool onWindowClose(WindowCloseEvent& e) override;
        virtual bool onWindowResize(WindowResizeEvent& e) override;
        virtual bool onWindowFramebufferResize(WindowFramebufferResizeEvent& e) override;
        virtual bool onWindowMinimize(WindowMinimizeEvent& e) override;

    private:
        static Application *s_instance;

        Scope<Window> m_window;
        Ref<ImguiLayer> m_imguiLayer;
        LayerStack m_layerStack;

        CommandLineArgs m_cmdArgs;
        WindowAPI m_windowAPI;
        RendererAPI m_rendererAPI;
        bool m_imguiEnabled;
        bool m_mimimized;
        bool m_running;
        int32_t m_exitCode;
    }; 

    mx::Ref<mx::Application> createApplication(const CommandLineArgs& args);
}