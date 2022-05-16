#pragma once

#include "mxpch.hpp"
#include "Events/EventsListener.hpp"
#include "utils/types.hpp"

namespace mx
{
    enum class WindowAPI
    {
        None = 0,
        GLFW,
    };

    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        bool Resizable = true;

        WindowProps(const std::string title = "App", uint32_t width = 800, uint32_t height = 600)
        :   Title(title), Width(width), Height(height)
        {}
    };

    class Window
    {
    public:
        
        static Scope<Window> Create(const WindowProps& props = WindowProps());
        
        virtual ~Window() = default;

        virtual void update() = 0;
        virtual void setVsync(bool vsync) = 0;
        virtual bool isVsync() const = 0;
        virtual bool isOpen() = 0;
        virtual void close() = 0;
        virtual void pushEventListnerLayer(mx::Ref<EventsListener> eventsListenerLayer) = 0;
        virtual void pushEventListnerOverlay(mx::Ref<EventsListener> eventsListenerOverlay) = 0;
        virtual bool removeEventsListener(mx::Ref<EventsListener> eventsListener) = 0;
        virtual void* getNativeWindow() = 0;

        virtual uint32_t getWidth() const  = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void setTitle(const std::string& title) = 0;
        virtual void resize(uint32_t width, uint32_t height) = 0;
        virtual void open() = 0;
    };
}