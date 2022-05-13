#pragma once

#include "utils/types.hpp"
#include "KeyCodes.hpp"
#include "MouseCodes.hpp"

namespace mx
{
    class Input
    {
    public:
        virtual ~Input() = default;

        static void init();

        static bool isKeyPressed(KeyCode key);
        static bool isKeyPressedOnce(KeyCode key);

        static bool isMouseButtonPressed(MouseCode mouseButton);
        static std::pair<float, float> getMousePos();
    protected:
        virtual bool isKeyPressedImpl(KeyCode key) = 0;

        virtual bool isMouseButtonPressedImpl(MouseCode mouseButton) = 0;
        virtual std::pair<float, float> getMousePosImpl() = 0;
    private:
        static Scope<Input> s_instance;

        std::unordered_set<KeyCode> m_pressedKeys;
    };
}