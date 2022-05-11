#pragma once

#include "Window.hpp"
#include "LayerStack.hpp"

namespace core
{
    class Application : public EventsListener, public std::enable_shared_from_this<Application>
    {
    public:
        Application();
        virtual ~Application();

        void pushLayer(utils::Ref<Layer> layer);
        void pushOverlay(utils::Ref<Layer> overlay);

        Window& getWindow() { return *m_window; }

        static Application& get() { return *s_instance; }


        void run();

    private:
        virtual void onEventReceive(Event& e) override;
        virtual bool onWindowClose(WindowCloseEvent& e) override;

    private:
        static Application *s_instance;

        Window *m_window;

        LayerStack m_layerStack;
    }; 

    Application* createApplication();
}