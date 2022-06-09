#pragma once

#include "Renderer/Buffer.hpp"
#include "utils/types.hpp"

#include <glad/glad.h>

namespace mx
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(void *vertices, uint32_t size);
        OpenGLVertexBuffer(uint32_t size);
        ~OpenGLVertexBuffer();
        
        virtual void bind() override;
        virtual void unbind() override;
        virtual void addSubData(void *vertices, uint32_t size,  uint32_t offset) override;

    private:
        RendererID m_bufferID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
        ~OpenGLIndexBuffer();
        
        virtual void bind() override;
        virtual void unbind() override;
        virtual uint32_t getCount() const override { return m_count; }

    private:
        RendererID m_bufferID;

        uint32_t m_count;
    };

}