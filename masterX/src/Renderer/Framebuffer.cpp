#include "mxpch.hpp"
#include "Framebuffer.hpp"

#include "core/Application.hpp"

#include "platform/OpenGL/OpenGLFramebuffer.hpp"

namespace mx
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (Application::get().getRendererAPI())
        {
            case RendererAPI::None: return nullptr;
            case RendererAPI::OpenGL: return Ref<OpenGLFramebuffer>::Create(spec);
        }

        MX_CORE_ASSERT(false, "Unkown rendering API");
        return nullptr;
    }
}