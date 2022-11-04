#pragma once

#include "core/Layer.hpp"

namespace mx
{
    class ImguiLayer : public Layer
    {
    public:
        virtual void onAttach() override;
        virtual void onDetach() override;
        
        virtual void onEventReceive(Event& e) override;

        void blockEvents(bool blockEvents) { m_blockEvents = blockEvents; }

        void begin();
        void end();

    private:
        bool m_blockEvents;

    };
}