#include "LayerStack.hpp"
#include "Log.hpp"

core::LayerStack::~LayerStack()
{
    for (auto layer : m_layers)
        layer->onDetach();
}

void core::LayerStack::pushLayer(utils::Ref<Layer> layer) 
{
    m_layers.push_back(layer);
}

void core::LayerStack::pushOverlay(utils::Ref<Layer> overlay) 
{
    m_layers.push_front(overlay);
}
