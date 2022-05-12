#include "mxpch.hpp"
#include "Window.hpp"

#include "Assert.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


static void errorCallback(int errorCode, const char *description)
{
    MX_CORE_ERROR("GLFW error occurred !! ({}) : {}", errorCode, description);
}


uint32_t mx::Window::s_WindowsCount = 0;

mx::Window::Window(const WindowProps& windowProps) 
{

    m_data.WindowProps = windowProps;

    MX_CORE_INFO("Creating Window {}, {}, {}", windowProps.Title, windowProps.Width, windowProps.Height);

    if (s_WindowsCount == 0)
    {
        int success = glfwInit();
        MX_CORE_ASSERT(success == GLFW_TRUE, "Cannot initialize glfw !! ");
        glfwSetErrorCallback(errorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    m_window = glfwCreateWindow(windowProps.Width, windowProps.Height, windowProps.Title.c_str(), nullptr, nullptr);
    MX_CORE_ASSERT(m_window != nullptr, "Cannot create window");
    glfwMakeContextCurrent(m_window);
    int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    MX_CORE_ASSERT(success, "Failed to initialize opengl");
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
        switch (action)
        {
            case GLFW_PRESS:
            {
                e = new KeyPressedEvent(key, false);
                break;
            }

            case GLFW_REPEAT:
            {
                e = new KeyPressedEvent(key, true);
                break;
            }

            case GLFW_RELEASE:
            {
                e = new KeyReleasedEvent(key);
                break;
            }
        }

        data.EventsQueue.push(e);
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        Event *e;
        switch (action)
        {
            case GLFW_PRESS:
            {
                e = new MouseButtonPressedEvent(button);
                break;
            }

            case GLFW_RELEASE:
            {
                e = new MouseButtonReleasedEvent(button);
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

mx::Window::~Window()
{
    MX_CORE_TRACE("Window destroyed");
    glfwDestroyWindow(m_window);
    s_WindowsCount--;
    if (s_WindowsCount == 0)
        glfwTerminate();
}

void mx::Window::handleEvents() 
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

void mx::Window::update() 
{
    handleEvents();

    glfwSwapBuffers(m_window);
}

void mx::Window::setVsync(bool vsync) 
{
    m_vsync = vsync;
    glfwSwapInterval(m_vsync ? 1 : 0);
}

bool mx::Window::isVsync() const 
{
    return m_vsync;    
}

bool mx::Window::isOpen() 
{
    return m_open;    
}

void mx::Window::close() 
{
    m_open = false;    
}

void mx::Window::pushEventListnerLayer(mx::Ref<EventsListener> eventsListenerLayer)
{
    m_eventListenersLayers.push_back(eventsListenerLayer);
}
        
void mx::Window::pushEventListnerOverlay(mx::Ref<EventsListener> eventsListenerOverlay)
{
    m_eventListenersLayers.push_front(eventsListenerOverlay);

}

bool mx::Window::removeEventsListener(mx::Ref<EventsListener> eventsListener)
{
    auto it = std::find(m_eventListenersLayers.begin(), m_eventListenersLayers.end(), eventsListener);

    if (it == m_eventListenersLayers.end())
        return false;

    m_eventListenersLayers.erase(it);

    return true;
}
