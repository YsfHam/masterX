#pragma once

#include "mxpch.hpp"
#include "utils/types.hpp"

namespace mx
{
    enum class FramebufferAttachementFormat
    {
        None = 0,

        // color
        RGB,

        // depth/stencil
        DEPTH24_STENCIL8

    };

    enum class FramebufferTextureFiltering
    {
        Nearest,
        Linear,
    };

    struct FramebufferAttachment
    {
        FramebufferAttachment(FramebufferAttachementFormat format)
            : Format(format)
        {}


        FramebufferAttachementFormat Format = FramebufferAttachementFormat::None;
        FramebufferTextureFiltering MinFiltering = FramebufferTextureFiltering::Linear;
        FramebufferTextureFiltering MagFiltering = FramebufferTextureFiltering::Linear;
    };

    struct FramebufferAttachments
    {
         FramebufferAttachments(const std::initializer_list<FramebufferAttachment>& attachements)
        : Attachements(attachements) {}
        FramebufferAttachments() = default;
        std::vector<FramebufferAttachment> Attachements;
    };

    struct FramebufferSpecification
    {
        FramebufferSpecification() = default;

        FramebufferAttachments Attachements;
        uint32_t Width, Height;
    };
    class Framebuffer
    {
    public:
        static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

        virtual void bind() = 0;
        virtual void unbind() = 0;
        
        virtual RendererID getColorAttachement(uint32_t index) = 0;

        virtual void resize(uint32_t width, uint32_t height) = 0;
        virtual const FramebufferSpecification& getSpecification() const = 0;
    };
}