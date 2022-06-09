#pragma once

#include "Color.hpp"
#include "VertexArray.hpp"

namespace mx
{
    // interface for rendering commands
    class RendererCommandsAPI
    {
    public:
        virtual ~RendererCommandsAPI() = default;
        virtual void setClearColor(const Color& clearColor = Color::Black) = 0;
        virtual void clear() = 0;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        virtual void drawIndexed(Ref<VertexArray>& vertexArray) = 0;
        virtual void drawIndexed(Ref<VertexArray>& vertexArray, uint32_t count) = 0;
    };
}