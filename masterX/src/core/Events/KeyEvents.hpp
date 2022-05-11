#pragma once
#include "mxpch.hpp"

#include "Events.hpp"

namespace core
{

    template<typename KeyEventType>
    class KeyEvent : public Event_Base<KeyEventType>
    {
    public:
        uint32_t getKeyCode() const { return m_keyCode; }
    
    protected:
        KeyEvent(uint32_t keyCode)
            : Event_Base<KeyEventType>(EventCategoryKeyboard),
            m_keyCode(keyCode)
        {}
    private:
        uint32_t m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent<KeyPressedEvent>
    {
    public:
        KeyPressedEvent(uint32_t keyCode, bool repeat)
            : KeyEvent(keyCode), m_repeat(repeat)
        {
        }

        bool allowRepeating() const { return m_repeat; }

        virtual std::string toString() const override
        {
            std::stringstream ss;
            ss << "Key pressed event " << getKeyCode();

            return ss.str();
        }

        static EventType getStaticType() { return EventType::KeyPressed; }

    private:
        bool m_repeat;
    };

    class KeyReleasedEvent : public KeyEvent<KeyReleasedEvent>
    {
    public:
        KeyReleasedEvent(uint32_t keyCode)
        : KeyEvent(keyCode)
        {}

        virtual std::string toString() const override
        {
            std::stringstream ss;
            ss << "Key released event " << getKeyCode();

            return ss.str();
        }

        static EventType getStaticType() { return EventType::KeyReleased; }
    };
}