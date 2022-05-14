#pragma once

#include "Renderer/RendererCommandsAPI.hpp"


namespace mx
{
    class OpenGLAPI : public RendererCommandsAPI
    {
    public:
        virtual void setClearColor(const Color& clearColor = Color::Black) override;
        virtual void clear() override;

        virtual void drawIndexed(Ref<VertexArray>& vertexArray) override;
    private:
        int m_clearFlags = 0;
    };
}