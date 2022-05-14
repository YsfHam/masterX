#include "mxpch.hpp"
#include "GraphicsContext.hpp"

#include "core/Application.hpp"

#include "platform/OpenGL/OpenGLContext.hpp"


mx::Scope<mx::GraphicsContext> mx::GraphicsContext::Create(void *windowHandle) 
{
    switch (Application::get().getRendererAPI())
    {
        case RendererAPI::None: return nullptr;
        case RendererAPI::OpenGL: return Scope<OpenGLContext>::Create(windowHandle);
    }

    MX_CORE_ASSERT(false, "Unknown renderer API");
    return nullptr;
}
