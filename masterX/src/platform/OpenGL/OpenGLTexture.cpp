#include "mxpch.hpp"
#include "OpenGLTexture.hpp"

#include <stb_image.h>
#include <glad/glad.h>

static GLint textureParam(mx::TextureOption option)
{
    if (option == mx::TextureOption::Linear)
        return GL_LINEAR;
    else if (option == mx::TextureOption::Nearest)
        return GL_NEAREST;

    return GL_NONE;
}

namespace mx
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
    {
        auto slashPos = filepath.find_last_of("/\\");
        auto extPos = filepath.find_last_of(".");
        m_name = filepath.substr(slashPos + 1, extPos - slashPos - 1);
        
        int channels;
        auto pixels = stbi_load(filepath.c_str(), (int*)&m_width, (int*)&m_height, &channels, 0);
        MX_CORE_ASSERT(pixels, "Could not load image from file {}", filepath);
        glGenTextures(1, &m_rendererID);
        glBindTexture(GL_TEXTURE_2D, m_rendererID);
        int format = GL_R8;
        if (channels == 3)
            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels);
        setParameters(Texture2DParameters());
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_width(width), m_height(height)
    {
        glGenTextures(1, &m_rendererID);
        glBindTexture(GL_TEXTURE_2D, m_rendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        setParameters(Texture2DParameters());
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture2D::bind(uint32_t activeLocation)
    {
        glActiveTexture(GL_TEXTURE0 + activeLocation);
        glBindTexture(GL_TEXTURE_2D, m_rendererID);
    }

    void OpenGLTexture2D::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    uint32_t OpenGLTexture2D::getWidth()
    {
        return m_width;
    }

    uint32_t OpenGLTexture2D::getHeight()
    {
        return m_height;
    }

    void OpenGLTexture2D::setParameters(const Texture2DParameters& parameters)
    {
        m_parameters = parameters;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureParam(parameters.MagFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureParam(parameters.MinFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureParam(parameters.WrapS));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureParam(parameters.WrapT));
    }
}