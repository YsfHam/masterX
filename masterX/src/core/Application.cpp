#include "mxpch.hpp"
#include "Application.hpp"

#include "Log.hpp"
#include "Assert.hpp"
#include "Input/Input.hpp"
#include "Timer.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/Renderer2D.hpp"


mx::Application *mx::Application::s_instance = nullptr;

mx::Application::Application(const AppSettings& settings) 
    : m_cmdArgs(settings.args), m_imguiEnabled(settings.EnableImGui),
    m_windowAPI(settings.WinAPI), m_rendererAPI(settings.GraphicsAPI),
    m_mimimized(false)
{
    MX_CORE_ASSERT(s_instance == nullptr, "Application already created");
    s_instance = this;

    MX_CORE_ASSERT(m_windowAPI != WindowAPI::None, "Window API must be specified");

    m_window = Window::Create(settings.WinProperties);
    Input::init();

    RendererCommand::init();
    Renderer2D::init();

    if (m_imguiEnabled)
    {
        m_imguiLayer = Ref<ImguiLayer>::Create();
        pushOverlay(m_imguiLayer);
    }
}

mx::Application::~Application() 
{
    Renderer2D::shutdown();
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
    m_window->pushEventListnerOverlay(shared_from_this());

    Timer timer;
    while (m_window->isOpen())
    {
        if (!m_mimimized)
        {
            for (auto layer : m_layerStack)
                layer->onUpdate(timer.restart());
        }

        if (m_imguiEnabled)
        {
            m_imguiLayer->begin();
            for (auto layer : m_layerStack)
                layer->onImguiRender();
            m_imguiLayer->end();
        }
        
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

bool mx::Application::onWindowResize(WindowResizeEvent& e)
{
    return false;
}

bool mx::Application::onWindowFramebufferResize(WindowFramebufferResizeEvent& e)
{
    RendererCommand::setViewport(0, 0, e.getWidth(), e.getHeight());
    return false;
}

bool mx::Application::onWindowMinimize(WindowMinimizeEvent& e)
{
    m_mimimized = e.Minimized;
    return false;
}
