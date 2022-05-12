#pragma once

#include "mxpch.hpp"
#include "Events/EventsListener.hpp"
#include "utils/types.hpp"

struct GLFWwindow;

namespace mx
{

    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string title = "App", uint32_t width = 800, uint32_t height = 600)
        :   Title(title), Width(width), Height(height)
        {}
    };

    class Window
    {
    public:
        Window(const WindowProps& windowProps = WindowProps());

        ~Window();

        void update();

        void setVsync(bool vsync);
        bool isVsync() const;

        bool isOpen();
        void close();

        void pushEventListnerLayer(mx::Ref<EventsListener> eventsListenerLayer);
        void pushEventListnerOverlay(mx::Ref<EventsListener> eventsListenerOverlay);

        bool removeEventsListener(mx::Ref<EventsListener> eventsListener);

        void* getNativeWindow() { return m_window; }

        uint32_t getWidth() const { return m_data.WindowProps.Width; }
        uint32_t getHeight() const { return m_data.WindowProps.Height; }

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
        bool m_vsync;
        bool m_open;
    };
}