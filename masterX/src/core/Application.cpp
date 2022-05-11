#include "mxpch.hpp"
#include "Application.hpp"

#include "Log.hpp"
#include "Assert.hpp"


core::Application *core::Application::s_instance = nullptr;

core::Application::Application() 
{
    MX_CORE_ASSERT(s_instance == nullptr, "Application already created");

    s_instance = this;

    m_window = new Window();
}

core::Application::~Application() 
{
    MX_CORE_FATAL("Bye");
}

void core::Application::pushLayer(utils::Ref<Layer> layer)
{
    layer->onAttach();
    m_layerStack.pushLayer(layer);
    m_window->pushEventListnerLayer(layer);
}

void core::Application::pushOverlay(utils::Ref<Layer> overlay)
{
    overlay->onAttach();
    m_layerStack.pushOverlay(overlay);
    m_window->pushEventListnerOverlay(overlay);
}

void core::Application::run() 
{
    m_window->pushEventListnerLayer(shared_from_this());

    while (m_window->isOpen())
    {
        for (auto layer : m_layerStack)
            layer->onUpdate();
        
        m_window->update();
    }

    delete m_window;
}

void core::Application::onEventReceive(Event& e)
{
}

bool core::Application::onWindowClose(WindowCloseEvent& e)
{
    m_window->close();

    return true;
}
