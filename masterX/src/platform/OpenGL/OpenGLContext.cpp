#include "mxpch.hpp"
#include "OpenGLContext.hpp"

#include "core/Application.hpp"

mx::OpenGLContext::OpenGLContext(void *windowHandle)
    : m_windowHandle(windowHandle)
{
    switch (Application::get().getWindowAPI())
    {
        case WindowAPI::None: break;
        case WindowAPI::GLFW:
        {
            glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_windowHandle));
            int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            MX_CORE_ASSERT(success, "Failed to initialize Glad");
            break;
        }

    }

    MX_CORE_INFO("OpenGL infos: ");
    MX_CORE_INFO("OpenGL renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    MX_CORE_INFO("OpenGL vendor:   {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    MX_CORE_INFO("OpenGL version:  {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

void mx::OpenGLContext::swapBuffers()
{
    switch (Application::get().getWindowAPI())
    {
        case WindowAPI::None: break;

        case WindowAPI::GLFW:
        {
            glfwSwapBuffers(static_cast<GLFWwindow*>(m_windowHandle));
            break;
        }
    }
}