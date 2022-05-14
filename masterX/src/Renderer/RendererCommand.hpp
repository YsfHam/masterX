#pragma once

#include "RendererCommandsAPI.hpp"
#include "utils/types.hpp"

namespace mx
{
    class RendererCommand
    {
    public:

        static void init();

        static void setClearColor(const Color& clearColor = Color::Black)
        {
            s_rendererAPI->setClearColor(clearColor);
        }

        static void clear()
        {
            s_rendererAPI->clear();
        }

        static void drawIndexed(Ref<VertexArray>& vertexArray)
        {
            s_rendererAPI->drawIndexed(vertexArray);
        }

    private:
        static Scope<RendererCommandsAPI> s_rendererAPI;
    };
}