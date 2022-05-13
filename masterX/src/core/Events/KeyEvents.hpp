#pragma once
#include "mxpch.hpp"

#include "Events.hpp"
#include "core/Input/KeyCodes.hpp"

namespace mx
{
    template<typename KeyEventType>
    class KeyEvent : public Event_Base<KeyEventType>
    {
    public:
        KeyCode getKeyCode() const { return m_keyCode; }
    
    protected:
        KeyEvent(KeyCode keyCode)
            : Event_Base<KeyEventType>(EventCategoryKeyboard | EventCategoryInput),
            m_keyCode(keyCode)
        {}
    private:
        KeyCode m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent<KeyPressedEvent>
    {
    public:
        KeyPressedEvent(KeyCode keyCode, bool repeat)
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
        KeyReleasedEvent(KeyCode keyCode)
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