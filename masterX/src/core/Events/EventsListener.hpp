#pragma once

#include "Events.hpp"
#include "KeyEvents.hpp"
#include "MouseEvents.hpp"
#include "WindowEvents.hpp"

#include "utils/macros.hpp"

namespace mx
{
    class EventsListener
    {
    protected:
        virtual bool onWindowClose(WindowCloseEvent& e) { return false; }
        virtual bool onWindowResize(WindowResizeEvent& e) { return false; }
        virtual bool onWindowFramebufferResize(WindowFramebufferResizeEvent& e) { return false; }
        virtual bool onWindowMinimize(WindowMinimizeEvent& e) { return false; }

        virtual bool onKeyPressed(KeyPressedEvent& e) { return false; }
        virtual bool onKeyReleased(KeyReleasedEvent& e) { return false; }

        virtual bool onMouseButtonPressed(MouseButtonPressedEvent& e) { return false; }
        virtual bool onMouseButtonReleased(MouseButtonReleasedEvent& e) { return false; }
        virtual bool onMouseMoved(MouseMovedEvent& e) { return false; }
        virtual bool onMouseScrolled(MouseScrolledEvent& e) { return false; }

        virtual void onEventReceive(Event& e) {}

    public:
        void onEvent(Event& e)
        {
            onEventReceive(e);
            
            EventDispatcher::dispatch<WindowCloseEvent>(e, MX_BIND_EVENT_FUNC(EventsListener::onWindowClose));
            EventDispatcher::dispatch<WindowResizeEvent>(e, MX_BIND_EVENT_FUNC(EventsListener::onWindowResize));
            EventDispatcher::dispatch<WindowFramebufferResizeEvent>(e, MX_BIND_EVENT_FUNC(EventsListener::onWindowFramebufferResize));
            EventDispatcher::dispatch<WindowMinimizeEvent>(e, MX_BIND_EVENT_FUNC(EventsListener::onWindowMinimize));

            EventDispatcher::dispatch<KeyPressedEvent>(e, MX_BIND_EVENT_FUNC(EventsListener::onKeyPressed));
            EventDispatcher::dispatch<KeyReleasedEvent>(e, MX_BIND_EVENT_FUNC(EventsListener::onKeyReleased));

            EventDispatcher::dispatch<MouseButtonPressedEvent>(e, MX_BIND_EVENT_FUNC(EventsListener::onMouseButtonPressed));
            EventDispatcher::dispatch<MouseButtonReleasedEvent>(e, MX_BIND_EVENT_FUNC(EventsListener::onMouseButtonReleased));
            EventDispatcher::dispatch<MouseMovedEvent>(e, MX_BIND_EVENT_FUNC(EventsListener::onMouseMoved));
            EventDispatcher::dispatch<MouseScrolledEvent>(e, MX_BIND_EVENT_FUNC(EventsListener::onMouseScrolled));
        }
    };
}