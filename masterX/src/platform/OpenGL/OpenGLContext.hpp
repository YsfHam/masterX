#pragma once

#include "Renderer/GraphicsContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace mx
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(void *windowHandle);

        virtual void swapBuffers() override;
    
    private:
        void *m_windowHandle;
    };
}