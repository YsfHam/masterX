#include "mxpch.hpp"
#include "Input.hpp"

#include "platform/glfw/GLFWInput.hpp"

mx::Scope<mx::Input> mx::Input::s_instance;

void mx::Input::init() 
{
    s_instance = Scope<GLFWInput>::Create();
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
