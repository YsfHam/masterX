#pragma once

#include "mxpch.hpp"
#include "Events/EventsListener.hpp"
#include "utils/types.hpp"

#include <GLFW/glfw3.h>

namespace core
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

        void pushEventListnerLayer(utils::Ref<EventsListener> eventsListenerLayer);
        void pushEventListnerOverlay(utils::Ref<EventsListener> eventsListenerOverlay);

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
        std::deque<utils::Ref<EventsListener>> m_eventListenersLayers;

        GLFWwindow *m_window;
        bool m_vsync;
        bool m_open;
    };
}