#pragma once

#include "Events/EventsListener.hpp"
#include "Timer.hpp"

namespace mx
{
    class Layer : public EventsListener
    {
    public:
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(Time dt) {}
        virtual void onImguiRender() {}
    };
}