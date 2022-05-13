#pragma once

#include "core/Input/KeyCodes.hpp"
#include "core/Input/MouseCodes.hpp"

namespace mx
{
    inline KeyCode getKeyCode(int glfwKeyCode)
    {
        return (KeyCode)glfwKeyCode;
    }

    inline int getGLFWKeyCode(KeyCode keyCode)
    {
        return (int)keyCode;
    }

    inline MouseCode getMouseCode(int glfwMouseCode)
    {
        return (MouseCode)glfwMouseCode;
    }

    inline int getGLFWMouseCode(MouseCode mouseCode)
    {
        return (int)mouseCode;
    }

}
