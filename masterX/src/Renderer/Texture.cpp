#include "mxpch.hpp"
#include "Texture.hpp"

#include "core/Application.hpp"
#include "platform/OpenGL/OpenGLTexture.hpp"

namespace mx
{
    Ref<Texture2D> Texture2D::Create(const std::string& filepath)
    {
        switch (Application::get().getRendererAPI())
        {
            case RendererAPI::None: return nullptr;
            case RendererAPI::OpenGL: return Ref<OpenGLTexture2D>::Create(filepath);
        }

        MX_CORE_ASSERT(false, "Unkown rendering API");
        return nullptr;
    }
    
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Application::get().getRendererAPI())
        {
            case RendererAPI::None: return nullptr;
            case RendererAPI::OpenGL: return Ref<OpenGLTexture2D>::Create(width, height);
        }

        MX_CORE_ASSERT(false, "Unkown rendering API");
        return nullptr;
    }
}