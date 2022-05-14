#include "mxpch.hpp"
#include "Window.hpp"

#include "core/Assert.hpp"
#include "core/Application.hpp"

#include "platform/glfw/GLFWWindow.hpp"

mx::Scope<mx::Window> mx::Window::Create(const WindowProps& props)
{
    switch (Application::get().getWindowAPI())
    {
        case WindowAPI::None: return nullptr;
        case WindowAPI::GLFW: return Scope<GLFWWindow>::Create(props);
    }

    MX_CORE_ASSERT(false, "Unknown window API");

    return nullptr;
}