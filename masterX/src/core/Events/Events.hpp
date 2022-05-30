#pragma once

#include "mxpch.hpp"

namespace mx
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFramebufferResize, WindowMinimize, WindowMaximize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None                     =    0,
        EventCategoryWindow      =    1 << 0,
        EventCategoryKeyboard    =    1 << 1,
        EventCategoryMouse       =    1 << 2,
        EventCategoryMouseButton =    1 << 3,
        EventCategoryInput       =    1 << 4,
    };

    class Event
    {
    public:
        virtual ~Event() = default;

        bool handled = false;

        int getCategoryFlag() const { return m_category; }
        virtual std::string toString() const = 0;
        virtual EventType getEventType() const = 0;


        bool isInCategory(EventCategory category)
        {
            return m_category & category;
        }

    protected:
        Event(int category)
            : m_category(category)
            {}

    private:
        int m_category;
    };

    template<typename T>
    class Event_Base : public Event
    {
    public:
        virtual EventType getEventType() const { return T::getStaticType(); }
        virtual std::string toString() const { return typeid(T).name(); }

    protected:
        Event_Base(int category) : Event(category)
        {}

    };

    class EventDispatcher
    {
    public:
        template<typename Ev>
        using EventFunc = std::function<bool(Ev&)>;

        template<typename Ev, typename T>
        static void dispatch(T& event, const EventFunc<Ev>& func)
        {
            if (event.getEventType() == Ev::getStaticType())
                event.handled |= func(reinterpret_cast<Ev&>(event));
        }
    };

    template<typename Ostream>
    inline Ostream& operator<<(Ostream& os, const Event& e)
    {
        fmt::format_to(std::ostream_iterator<char>(os), e.toString());
        return os;
    }

}