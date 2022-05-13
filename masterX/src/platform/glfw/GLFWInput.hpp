#pragma once


#include "core/Input/Input.hpp"

namespace mx
{
    class GLFWInput : public Input
    {
    public:
        virtual bool isKeyPressedImpl(KeyCode key) override;

        virtual bool isMouseButtonPressedImpl(MouseCode mouseButton) override;
        virtual std::pair<float, float> getMousePosImpl() override;

    private:
        std::unordered_set<KeyCode> m_pressedKeys;
    };
}