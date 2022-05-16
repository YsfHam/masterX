#include "mxpch.hpp"
#include "Application.hpp"

#include "Log.hpp"
#include "Assert.hpp"
#include "Input/Input.hpp"
#include "Renderer/Renderer.hpp"

//#include "math3D/math3D.hpp"

#include <chrono>


mx::Application *mx::Application::s_instance = nullptr;

mx::Application::Application(const AppSettings& settings) 
    : m_cmdArgs(settings.args), m_imguiEnabled(settings.EnableImGui),
    m_windowAPI(settings.WinAPI), m_rendererAPI(settings.GraphicsAPI)
{
    MX_CORE_ASSERT(s_instance == nullptr, "Application already created");
    s_instance = this;

    MX_CORE_ASSERT(m_windowAPI != WindowAPI::None, "Window API must be specified");

    m_window = Window::Create(settings.WinProperties);
    Input::init();
    RendererCommand::init();

    if (m_imguiEnabled)
    {
        m_imguiLayer = Ref<ImguiLayer>::Create();
        pushOverlay(m_imguiLayer);
    }
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

    auto currentFrame = std::chrono::system_clock::now();
    auto lastFrame = std::chrono::system_clock::now();
    while (m_window->isOpen())
    {
        currentFrame = std::chrono::system_clock::now();
        std::chrono::duration<float> duration = currentFrame - lastFrame;
        
        float dt = duration.count();
        lastFrame = currentFrame;


        for (auto layer : m_layerStack)
            layer->onUpdate(dt);

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
