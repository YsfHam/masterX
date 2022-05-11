#pragma once


#include "Events.hpp"

namespace core
{
    class WindowCloseEvent : public Event_Base<WindowCloseEvent>
    {
    public:
        WindowCloseEvent() : Event_Base(EventCategoryWindow) {}
        static EventType getStaticType() { return EventType::WindowClose; }
    };

    class WindowResizeEvent : public Event_Base<WindowResizeEvent>
    {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height) 
        : Event_Base(EventCategoryWindow), m_width(width), m_height(height)
        {}
        static EventType getStaticType() { return EventType::WindowResize; }

        uint32_t getWidth() { return m_width; }
        uint32_t getHeight() { return m_height; }

        virtual std::string toString() const override
        {
            std::stringstream ss;
            ss << "Window Resized to " << m_width << ' ' << m_height;
            return ss.str();
        }

    private:
        uint32_t m_width;
        uint32_t m_height;
    };
}