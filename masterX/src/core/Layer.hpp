#pragma once

#include "Events/EventsListener.hpp"

namespace mx
{
    class Layer : public EventsListener
    {
    public:
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(float dt) {}
        virtual void onImguiRender() {}
    };
}