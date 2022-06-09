#pragma once

#include "core/AssetsManager.hpp"

namespace mx
{
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

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string& filepath);
        static Ref<Texture2D> Create(uint32_t width, uint32_t height);
    };
}