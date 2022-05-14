#include "mxpch.hpp"
#include "GLFWWindow.hpp"

#include "core/Assert.hpp"
#include "GLFWInputCodes.hpp"
#include "core/Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


static void errorCallback(int errorCode, const char *description)
{
    MX_CORE_ERROR("GLFW error occurred !! ({}) : {}", errorCode, description);
}


uint32_t mx::GLFWWindow::s_WindowsCount = 0;

mx::GLFWWindow::GLFWWindow(const WindowProps& windowProps) 
{

    m_data.WindowProps = windowProps;

    MX_CORE_INFO("Creating Window {}, {}, {}", windowProps.Title, windowProps.Width, windowProps.Height);

    if (s_WindowsCount == 0)
    {
        int success = glfwInit();
        MX_CORE_ASSERT(success == GLFW_TRUE, "Cannot initialize glfw !! ");
        glfwSetErrorCallback(errorCallback);

    }
    if (Application::get().getRendererAPI() == RendererAPI::OpenGL)
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    }

    m_window = glfwCreateWindow(windowProps.Width, windowProps.Height, windowProps.Title.c_str(), nullptr, nullptr);
    MX_CORE_ASSERT(m_window != nullptr, "Cannot create window");

    m_context = GraphicsContext::Create(m_window);

    m_open = true;
    setVsync(true);
    s_WindowsCount++;

    glfwSetWindowUserPointer(m_window, &m_data);

    // glfw callbacks

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        data.EventsQueue.push(new WindowCloseEvent);
    });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        data.WindowProps.Width = width;
        data.WindowProps.Height = height;

        data.EventsQueue.push(new WindowResizeEvent(width, height));
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        Event *e;
        KeyCode keyCode = getKeyCode(key);
        switch (action)
        {
            case GLFW_PRESS:
            {
                e = new KeyPressedEvent(keyCode, false);
                break;
            }

            case GLFW_REPEAT:
            {
                e = new KeyPressedEvent(keyCode, true);
                break;
            }

            case GLFW_RELEASE:
            {
                e = new KeyReleasedEvent(keyCode);
                break;
            }
        }

        data.EventsQueue.push(e);
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        Event *e;
        MouseCode buttonCode = getMouseCode(button);
        switch (action)
        {
            case GLFW_PRESS:
            {
                e = new MouseButtonPressedEvent(buttonCode);
                break;
            }

            case GLFW_RELEASE:
            {
                e = new MouseButtonReleasedEvent(buttonCode);
                break;
            }
        }

        data.EventsQueue.push(e);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xpos, double ypos){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        data.EventsQueue.push(new MouseMovedEvent((float)xpos, (float)ypos));
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xoffset, double yoffset){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        data.EventsQueue.push(new MouseScrolledEvent((float)xoffset, (float)yoffset));
    });


}

mx::GLFWWindow::~GLFWWindow()
{
    MX_CORE_TRACE("Window destroyed");
    glfwDestroyWindow(m_window);
    s_WindowsCount--;
    if (s_WindowsCount == 0)
        glfwTerminate();
}

void mx::GLFWWindow::handleEvents() 
{
    glfwPollEvents();

    while (!m_data.EventsQueue.empty())
    {
        Event* e = m_data.EventsQueue.front();
        m_data.EventsQueue.pop();

        for (auto eventListener : m_eventListenersLayers)
        {
            eventListener->onEvent(*e);
            if (e->handled)
                break;
        }

        delete e;

    }
}

void mx::GLFWWindow::update() 
{
    handleEvents();

    m_context->swapBuffers();
}

void mx::GLFWWindow::setVsync(bool vsync) 
{
    m_vsync = vsync;
    glfwSwapInterval(m_vsync ? 1 : 0);
}

bool mx::GLFWWindow::isVsync() const 
{
    return m_vsync;    
}

bool mx::GLFWWindow::isOpen() 
{
    return m_open;    
}

void mx::GLFWWindow::close() 
{
    m_open = false;    
}

void mx::GLFWWindow::pushEventListnerLayer(mx::Ref<EventsListener> eventsListenerLayer)
{
    m_eventListenersLayers.push_back(eventsListenerLayer);
}
        
void mx::GLFWWindow::pushEventListnerOverlay(mx::Ref<EventsListener> eventsListenerOverlay)
{
    m_eventListenersLayers.push_front(eventsListenerOverlay);

}

bool mx::GLFWWindow::removeEventsListener(mx::Ref<EventsListener> eventsListener)
{
    auto it = std::find(m_eventListenersLayers.begin(), m_eventListenersLayers.end(), eventsListener);

    if (it == m_eventListenersLayers.end())
        return false;

    m_eventListenersLayers.erase(it);

    return true;
}

void mx::GLFWWindow::setTitle(const std::string& title)
{
    glfwSetWindowTitle(m_window, title.c_str());
}

void mx::GLFWWindow::resize(uint32_t width, uint32_t height)
{
    glfwSetWindowSize(m_window, width, height);
}

void mx::GLFWWindow::open()
{
    m_open = true;
}

