#pragma once

#include "mxpch.hpp"
#include "Layer.hpp"
#include "utils/types.hpp"

namespace core
{
    class LayerStack
    {
    public:
        ~LayerStack();
        void pushLayer(utils::Ref<Layer> layer);
        void pushOverlay(utils::Ref<Layer> overlay);


        std::deque<utils::Ref<Layer>>::iterator begin() {return m_layers.begin(); }
        std::deque<utils::Ref<Layer>>::iterator end() {return m_layers.end(); }


    private:
        std::deque<utils::Ref<Layer>> m_layers;
    };
}