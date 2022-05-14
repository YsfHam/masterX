#include "mxpch.hpp"
#include "Buffer.hpp"

#include "core/Application.hpp"

#include "platform/OpenGL/OpenGLBuffer.hpp"

namespace mx
{
    Ref<VertexBuffer> VertexBuffer::Create(void *vertices, uint32_t size)
    {
        switch (Application::get().getRendererAPI())
        {
            case RendererAPI::None: return nullptr;
            case RendererAPI::OpenGL: return Ref<OpenGLVertexBuffer>::Create(vertices, size);
        }

        MX_CORE_ASSERT(false, "Unknown renderer API");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        return Create(nullptr, size);
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count)
    {
        switch (Application::get().getRendererAPI())
        {
            case RendererAPI::None: return nullptr;
            case RendererAPI::OpenGL: return Ref<OpenGLIndexBuffer>::Create(indices, count);
        }

        MX_CORE_ASSERT(false, "Unknown renderer API");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t count)
    {
        return Create(nullptr, count);
    }
}