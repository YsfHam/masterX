#pragma once

#include "Renderer/VertexArray.hpp"
#include "utils/types.hpp"

namespace mx
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        virtual void bind() override;
        virtual void unbind() override;
        virtual void addVertexBuffer(Ref<VertexBuffer> vertexBuffer) override;
        virtual void setIndexBuffer(Ref<IndexBuffer> indexBuffer) override;

        virtual Ref<VertexBuffer>& getVertexBuffer(uint32_t index) override;
        virtual Ref<IndexBuffer>& getIndexBuffer() override;

    private:
        RendererID m_vertexArrayID;

        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    };
}