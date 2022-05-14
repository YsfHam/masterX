#pragma once

#include "Buffer.hpp"

namespace mx
{
    class VertexArray
    {
    public:
        static Ref<VertexArray> Create();

        virtual ~VertexArray() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void addVertexBuffer(Ref<VertexBuffer> vertexBuffer) = 0;
        virtual void setIndexBuffer(Ref<IndexBuffer> indexBuffer) = 0;

        virtual Ref<VertexBuffer>& getVertexBuffer(uint32_t index) = 0;
        virtual Ref<IndexBuffer>& getIndexBuffer() = 0;
    };
}