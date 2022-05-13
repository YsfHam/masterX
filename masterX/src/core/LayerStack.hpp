#pragma once

#include "mxpch.hpp"
#include "Layer.hpp"
#include "utils/types.hpp"

namespace mx
{
    class LayerStack
    {
    public:
        ~LayerStack();
        void pushLayer(mx::Ref<Layer> layer);
        void pushOverlay(mx::Ref<Layer> overlay);

        void popLayer(Ref<Layer> layer);


        std::deque<mx::Ref<Layer>>::iterator begin() {return m_layers.begin(); }
        std::deque<mx::Ref<Layer>>::iterator end() {return m_layers.end(); }


    private:
        std::deque<mx::Ref<Layer>> m_layers;
    };
}