#include "mxpch.hpp"
#include "VertexArray.hpp"

#include "core/Application.hpp"

#include "platform/OpenGL/OpenGLVertexArray.hpp"

mx::Ref<mx::VertexArray> mx::VertexArray::Create()
{
    switch (Application::get().getRendererAPI())
    {
        case RendererAPI::None: return nullptr;
        case RendererAPI::OpenGL: return Ref<OpenGLVertexArray>::Create();
    }

    MX_CORE_ASSERT(false, "Unknown renderer API");
    return nullptr;
}