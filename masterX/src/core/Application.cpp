#include "mxpch.hpp"
#include "Application.hpp"

#include "Log.hpp"
#include "Assert.hpp"

#include <glad/glad.h>


mx::Application *mx::Application::s_instance = nullptr;

mx::Application::Application() 
{
    MX_CORE_ASSERT(s_instance == nullptr, "Application already created");
    s_instance = this;

    m_window = std::make_unique<Window>();

    m_imguiLayer = Ref<ImguiLayer>::Create();
    pushOverlay(m_imguiLayer);
}

mx::Application::~Application() 
{
    MX_CORE_FATAL("Bye");
}

void mx::Application::pushLayer(mx::Ref<Layer> layer)
{
    layer->onAttach();
    m_layerStack.pushLayer(layer);
    m_window->pushEventListnerLayer(layer);
}

void mx::Application::pushOverlay(mx::Ref<Layer> overlay)
{
    overlay->onAttach();
    m_layerStack.pushOverlay(overlay);
    m_window->pushEventListnerOverlay(overlay);
}

void mx::Application::run() 
{
    m_window->pushEventListnerLayer(shared_from_this());

    while (m_window->isOpen())
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto layer : m_layerStack)
            layer->onUpdate();

        m_imguiLayer->begin();
        for (auto layer : m_layerStack)
            layer->onImguiRender();
        m_imguiLayer->end();
        
        m_window->update();
    }

    m_window->removeEventsListener(shared_from_this());

}

void mx::Application::onEventReceive(Event& e)
{
}

bool mx::Application::onWindowClose(WindowCloseEvent& e)
{
    m_window->close();

    return true;
}
