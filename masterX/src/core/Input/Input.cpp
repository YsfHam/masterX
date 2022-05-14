#include "mxpch.hpp"
#include "Input.hpp"

#include "core/Application.hpp"

#include "platform/glfw/GLFWInput.hpp"

mx::Scope<mx::Input> mx::Input::s_instance;

void mx::Input::init() 
{
    WindowAPI api = Application::get().getWindowAPI();
    switch (api)
    {
        case WindowAPI::None: s_instance = nullptr; break;
        case WindowAPI::GLFW: s_instance = Scope<GLFWInput>::Create(); break;

        default:
        {
            MX_CORE_ASSERT(false, "Unknown window API");
        }
    }
}

bool mx::Input::isKeyPressed(KeyCode key) 
{
    return s_instance->isKeyPressedImpl(key);
}

bool mx::Input::isKeyPressedOnce(KeyCode key)
{
    bool keyPressed = isKeyPressed(key);

    auto it = s_instance->m_pressedKeys.find(key);

    if (keyPressed && it == s_instance->m_pressedKeys.end())
    {
        s_instance->m_pressedKeys.emplace(key);
        return true;
    }
    else if(!keyPressed && it != s_instance->m_pressedKeys.end())
        s_instance->m_pressedKeys.erase(it);

    return false;
}

bool mx::Input::isMouseButtonPressed(MouseCode mouseButton) 
{
    return s_instance->isMouseButtonPressedImpl(mouseButton);
    
}

std::pair<float, float> mx::Input::getMousePos() 
{
    return s_instance->getMousePosImpl();
}
