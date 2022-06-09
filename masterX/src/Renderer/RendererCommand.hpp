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

        static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_rendererAPI->setViewport(x, y, width, height);
        }

        static void drawIndexed(Ref<VertexArray>& vertexArray)
        {
            s_rendererAPI->drawIndexed(vertexArray);
        }

        static void drawIndexed(Ref<VertexArray>& vertexArray, uint32_t count)
        {
            s_rendererAPI->drawIndexed(vertexArray, count);
        }

    private:
        static Scope<RendererCommandsAPI> s_rendererAPI;
    };
}