#include "mxpch.hpp"
#include "GLFWInput.hpp"

#include "core/Application.hpp"
#include "GLFWInputCodes.hpp"

#include <GLFW/glfw3.h>

bool mx::GLFWInput::isKeyPressedImpl(KeyCode key)
{
    GLFWwindow *window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());

    int status = glfwGetKey(window, getGLFWKeyCode(key));

    return status == GLFW_PRESS;
}

bool mx::GLFWInput::isMouseButtonPressedImpl(MouseCode mouseButton)
{
    GLFWwindow *window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());

    int status = glfwGetMouseButton(window, getGLFWMouseCode(mouseButton));

    return status == GLFW_PRESS;
}

std::pair<float, float> mx::GLFWInput::getMousePosImpl()
{
    GLFWwindow *window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return {x, y};
}