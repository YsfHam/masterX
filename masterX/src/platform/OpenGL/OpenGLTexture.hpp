#pragma once

#include "Renderer/Texture.hpp"

namespace mx
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& filepath);
        OpenGLTexture2D(uint32_t width, uint32_t height);

        virtual void bind(uint32_t activeLocation = 0) override;
        virtual void unbind() override;

        virtual uint32_t getWidth() override;
        virtual uint32_t getHeight() override;

        virtual void setParameters(const Texture2DParameters& parameters) override;
        virtual Texture2DParameters getParameters() const override { return m_parameters; }

        virtual void setTillingFactor(float factor) override { m_parameters.TillingFactor = factor; };
        virtual float getTillingFactor() const override { return m_parameters.TillingFactor; };

        virtual uint32_t getID() const override { return m_rendererID; };

        virtual std::string getName() const override { return m_name; }

    private:
        uint32_t m_width;
        uint32_t m_height;

        RendererID m_rendererID;

        std::string m_name;

        Texture2DParameters m_parameters;
    };
}