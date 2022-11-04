#pragma once

#include "Renderer/Framebuffer.hpp"

#include "core/Assert.hpp"

namespace mx
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        ~OpenGLFramebuffer();

        virtual void bind() override;
        virtual void unbind() override;

        virtual RendererID getColorAttachement(uint32_t index) override
        {
            MX_CORE_ASSERT(index < m_colorAttachmentsIDs.size(), "index out of bound");
            return m_colorAttachmentsIDs[index];
        }

        void init();
        virtual void resize(uint32_t width, uint32_t height) override;
        virtual const FramebufferSpecification& getSpecification() const override { return m_spec; }

    private:
        FramebufferSpecification m_spec;

        RendererID m_rendererID;

        std::vector<FramebufferAttachment> m_colorAttachments;
        FramebufferAttachment m_depthAttachment;

        std::vector<RendererID> m_colorAttachmentsIDs;
        RendererID m_depthAttachmentID;

    };
}