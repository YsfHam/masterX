#pragma once

#include "core/Window.hpp"

#include "Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace mx
{

    class GLFWWindow : public Window
    {
    public:
        GLFWWindow(const WindowProps& windowProps = WindowProps());

        ~GLFWWindow();

        virtual void update() override;
        virtual void setVsync(bool vsync) override;
        virtual bool isVsync() const override;
        virtual bool isOpen() override;
        virtual void close() override;
        virtual void pushEventListnerLayer(mx::Ref<EventsListener> eventsListenerLayer) override;
        virtual void pushEventListnerOverlay(mx::Ref<EventsListener> eventsListenerOverlay) override;
        virtual bool removeEventsListener(mx::Ref<EventsListener> eventsListener) override;
        virtual void* getNativeWindow() override { return m_window; }
        virtual uint32_t getWidth() const  override { return m_data.WindowProps.Width; }
        virtual uint32_t getHeight() const override { return m_data.WindowProps.Height; }

        virtual void setTitle(const std::string& title) override;
        virtual void resize(uint32_t width, uint32_t height) override;
        virtual void open() override;

    private:
        struct WindowData
        {
            WindowProps WindowProps;

            std::queue<Event*> EventsQueue;
        };

    private:
        void handleEvents();

    private:
        static uint32_t s_WindowsCount;

        WindowData m_data;
        std::deque<mx::Ref<EventsListener>> m_eventListenersLayers;

        GLFWwindow *m_window;

        Scope<GraphicsContext> m_context;

        bool m_vsync;
        bool m_open;
    };
}