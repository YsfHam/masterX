#include "mxpch.hpp"
#include "Window.hpp"

#include "platform/glfw/GLFWWindow.hpp"

std::unique_ptr<mx::Window> mx::Window::Create(const WindowProps& props)
{
    return std::make_unique<GLFWWindow>(props);
}