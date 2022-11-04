#pragma once

#include "core/AssetsManager.hpp"
#include <glm/glm.hpp>
namespace mx
{
    enum class TextureOption
    {
        // texture min, mag
        Nearest,
        Linear,

        // for texture wrap
        Repeat,
        ClampToEdge,
        ClampToBorder,
        MirroredRepeat

    };
    class Texture : public Asset
    {
    public:
        virtual ~Texture() = default;

        virtual void bind(uint32_t activeLocation = 0) = 0;
        virtual void unbind() = 0;

        virtual uint32_t getWidth() = 0;
        virtual uint32_t getHeight() = 0;

        virtual uint32_t getID() const = 0;
    };

    struct Texture2DParameters
    {
        TextureOption MinFilter = TextureOption::Nearest;  
        TextureOption MagFilter = TextureOption::Nearest;  
        TextureOption WrapS = TextureOption::Repeat;  
        TextureOption WrapT = TextureOption::Repeat;  

        float TillingFactor = 1.0f;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string& filepath);
        static Ref<Texture2D> Create(uint32_t width, uint32_t height);

        virtual void setParameters(const Texture2DParameters& parameters) = 0;
        virtual Texture2DParameters getParameters() const = 0;

        virtual void setTillingFactor(float factor) = 0;
        virtual float getTillingFactor() const = 0;
    };

    class SubTexture2D
    {
    public:
        static Ref<SubTexture2D> Create(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& size);

        SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
        
        Ref<Texture2D> getTexture() { return m_texture; }
        const glm::vec2* getTextureCoords() const { return m_textureCoords; }
    private:
        Ref<Texture2D> m_texture;
        glm::vec2 m_textureCoords[4];
    };
}