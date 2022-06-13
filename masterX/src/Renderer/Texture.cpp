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


    Ref<SubTexture2D> SubTexture2D::Create(const Ref<Texture2D>& texture, const math3D::Vector2f& coords, const math3D::Vector2f& size)
    {
        math3D::Vector2f min = {
            (coords.x * size.x) / texture->getWidth(),
            (coords.y * size.y) / texture->getHeight()
        };

        math3D::Vector2f max = {
            ((coords.x  + 1)* size.x) / texture->getWidth(),
            ((coords.y + 1) * size.y) / texture->getHeight()
        };

        return Ref<SubTexture2D>::Create(texture, min, max);
    }

    SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const math3D::Vector2f& min, const math3D::Vector2f& max)
        :
        m_texture(texture),
        m_textureCoords{
            {min.x, max.y},
            {max.x, max.y},
            {max.x, min.y},
            {min.x, min.y}
        }
    {
    }
}