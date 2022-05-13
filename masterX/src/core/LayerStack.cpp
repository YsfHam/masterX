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

void mx::LayerStack::popLayer(Ref<Layer> layer)
{
    auto it = std::find(m_layers.begin(), m_layers.end(), layer);
    if (it != m_layers.end())
    {
        layer->onDetach();
        m_layers.erase(it);
    }
}
