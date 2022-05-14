#pragma once

#include "utils/types.hpp"

namespace mx
{

    enum class RendererAPI
    {
        None = 0,
        OpenGL,
    };

    class GraphicsContext
    {
    public:
        static Scope<GraphicsContext> Create(void *windowHandle);

        virtual ~GraphicsContext() = default;

        virtual void swapBuffers() = 0;
    };
}