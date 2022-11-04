#include "mxpch.hpp"
#include "OpenGLFramebuffer.hpp"

#include "core/Assert.hpp"

#include <glad/glad.h>

void initTexture(mx::RendererID id, uint32_t width, uint32_t height, GLenum format)
{
    switch (format)
    {
        case GL_RGB:
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            break;
        }
        case GL_DEPTH24_STENCIL8:
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
            break;
        }
    }
}

void setTextureFiltering(GLint minFilter, GLint magFilter)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

GLenum getTextureFormat(mx::FramebufferAttachementFormat format)
{
    switch (format)
    {
        case mx::FramebufferAttachementFormat::RGB: return GL_RGB;
        case mx::FramebufferAttachementFormat::DEPTH24_STENCIL8: return GL_DEPTH24_STENCIL8;

        default: break;
    }

    return GL_NONE;
}

GLint getTextureFiltering(mx::FramebufferTextureFiltering filtering)
{
    switch (filtering)
    {
        case mx::FramebufferTextureFiltering::Linear: return GL_LINEAR;
        case mx::FramebufferTextureFiltering::Nearest: return GL_NEAREST;
    }

    return GL_NONE;
}

bool isDepthAttachement(mx::FramebufferAttachementFormat format)
{
    switch (format)
    {
        case mx::FramebufferAttachementFormat::DEPTH24_STENCIL8: return true;

        default: return false;
    }

    return false;
}


namespace mx
{
    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
    : m_spec(spec),
    m_depthAttachment(mx::FramebufferAttachementFormat::None)
    {
        for (auto& attachement : spec.Attachements.Attachements)
        {
            if (isDepthAttachement(attachement.Format))
                m_depthAttachment = attachement;
            else
                m_colorAttachments.emplace_back(attachement);
        }
        m_colorAttachmentsIDs.resize(m_colorAttachments.size());
        init();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &m_rendererID);
        glDeleteTextures(m_colorAttachmentsIDs.size(), m_colorAttachmentsIDs.data());
        glDeleteTextures(1, &m_depthAttachmentID);
    }

    void OpenGLFramebuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
    }

    void OpenGLFramebuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::init()
    {
        glGenFramebuffers(1, &m_rendererID);

        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);

        if (m_colorAttachmentsIDs.size() > 0)
            glGenTextures(m_colorAttachmentsIDs.size(), m_colorAttachmentsIDs.data());
        std::vector<GLenum> attachements;
        attachements.resize(m_colorAttachmentsIDs.size());
        for (uint32_t i(0); i < m_colorAttachmentsIDs.size(); i++)
        {
            glBindTexture(GL_TEXTURE_2D, m_colorAttachmentsIDs[i]);
            initTexture(m_colorAttachmentsIDs[i], m_spec.Width, m_spec.Height, getTextureFormat(m_colorAttachments[i].Format));
            setTextureFiltering(getTextureFiltering(m_colorAttachments[i].MinFiltering), getTextureFiltering(m_colorAttachments[i].MagFiltering));

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_colorAttachmentsIDs[i], 0);
            attachements[i] = GL_COLOR_ATTACHMENT0 + i;
        }

        if (attachements.size() > 0)
            glDrawBuffers(attachements.size(), attachements.data());

        if (m_depthAttachment.Format != FramebufferAttachementFormat::None)
        {
            glGenTextures(1, &m_depthAttachmentID);
            glBindTexture(GL_TEXTURE_2D, m_depthAttachmentID);
            initTexture(m_depthAttachmentID, m_spec.Width, m_spec.Height, getTextureFormat(m_depthAttachment.Format));
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachmentID, 0);
        }

        MX_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete !");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::resize(uint32_t width, uint32_t height)
    {
        if (width != m_spec.Width || height != m_spec.Height)
        {
            m_spec.Width = width;
            m_spec.Height = height;

            glDeleteFramebuffers(1, &m_rendererID);
            glDeleteTextures(m_colorAttachmentsIDs.size(), m_colorAttachmentsIDs.data());
            glDeleteTextures(1, &m_depthAttachmentID);

            init();
        }
    }
}