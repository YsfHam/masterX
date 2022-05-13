#pragma once

#include "Events.hpp"
#include "core/Input/MouseCodes.hpp"


namespace mx
{
    class MouseButtonPressedEvent : public Event_Base<MouseButtonPressedEvent>
    {
    public:
        MouseButtonPressedEvent(MouseCode mouseButton)
            : Event_Base(EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput),
            m_mouseButton(mouseButton)
        {}

        static EventType getStaticType() { return EventType::MouseButtonPressed; }
        virtual std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse button pressed " << m_mouseButton;
            return ss.str();
        }

        MouseCode getMouseButtonCode() { return m_mouseButton; }

    private:
        MouseCode m_mouseButton;
    };

    class MouseButtonReleasedEvent : public Event_Base<MouseButtonReleasedEvent>
    {
    public:
        MouseButtonReleasedEvent(MouseCode mouseButton)
            : Event_Base(EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput),
            m_mouseButton(mouseButton)
        {}

        static EventType getStaticType() { return EventType::MouseButtonReleased; }
        virtual std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse button released " << m_mouseButton;
            return ss.str();
        }

    private:
        MouseCode m_mouseButton;
    };

    class MouseMovedEvent : public Event_Base<MouseMovedEvent>
    {
    public:
        MouseMovedEvent(float mouseX, float mouseY)
            : Event_Base(EventCategoryMouse | EventCategoryInput),
            m_mouseX(mouseX), m_mouseY(mouseY)
        {}

        float getMouseX() const { return m_mouseX; }
        float getMouseY() const { return m_mouseY; }

        static EventType getStaticType() { return EventType::MouseMoved; }
        virtual std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse moved event " << m_mouseX << ' ' << m_mouseY;
            return ss.str();
        }

    private:
        float m_mouseX, m_mouseY;
    };

    class MouseScrolledEvent : public Event_Base<MouseScrolledEvent>
    {
    public:
        MouseScrolledEvent(float offsetX, float offsetY)
            : Event_Base(EventCategoryMouse | EventCategoryInput),
            m_offsetX(offsetX), m_offsetY(offsetY)
        {}

        float getScrollOffsetX() const { return m_offsetX; }
        float getScrollOffsetY() const { return m_offsetY; }

        static EventType getStaticType() { return EventType::MouseScrolled; }
        virtual std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse moved event " << m_offsetX << ' ' << m_offsetY;
            return ss.str();
        }

    private:
        float m_offsetX, m_offsetY;
    };
}