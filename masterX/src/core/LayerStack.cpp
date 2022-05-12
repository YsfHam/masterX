#include "LayerStack.hpp"
#include "Log.hpp"

mx::LayerStack::~LayerStack()
{
    MX_CORE_TRACE("Layers detaching...");
    for (auto layer : m_layers)
        layer->onDetach();
}

void mx::LayerStack::pushLayer(mx::Ref<Layer> layer) 
{
    m_layers.push_back(layer);
}

void mx::LayerStack::pushOverlay(mx::Ref<Layer> overlay) 
{
    m_layers.push_front(overlay);
}
