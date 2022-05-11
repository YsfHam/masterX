#pragma once

#include "Events/EventsListener.hpp"

namespace core
{
    class Layer : public EventsListener
    {
    public:
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
    };
}