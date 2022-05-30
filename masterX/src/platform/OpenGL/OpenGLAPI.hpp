#pragma once

#include "Renderer/RendererCommandsAPI.hpp"


namespace mx
{
    class OpenGLAPI : public RendererCommandsAPI
    {
    public:
        OpenGLAPI();
        virtual void setClearColor(const Color& clearColor = Color::Black) override;
        virtual void clear() override;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        virtual void drawIndexed(Ref<VertexArray>& vertexArray) override;
    private:
        int m_clearFlags = 0;
    };
}