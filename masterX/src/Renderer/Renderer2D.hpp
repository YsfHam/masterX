#pragma once

#include "math3D/math3D.hpp"

#include "Renderer/Color.hpp"
#include "Renderer/Camera2D.hpp"
#include "Renderer/Texture.hpp"

namespace mx
{
    class Renderer2D
    {
    public:
        static void init();
        static void shutdown();

        static void beginScene(Camera2D& camera);
        static void endScene();

        static void drawQuad(const math3D::Vector2f& position, const math3D::Vector2f& size, const Color& color, const math3D::Angle& angle, const Ref<Texture2D>& texture);
        static void drawQuad(const math3D::Vector2f& position, const math3D::Vector2f& size, const Color& color, const Ref<Texture2D>& texture);
        static void drawQuad(const math3D::Vector2f& position, const math3D::Vector2f& size, const math3D::Angle& angle, const Ref<Texture2D>& texture);
        static void drawQuad(const math3D::Vector2f& position, const math3D::Vector2f& size, const Ref<Texture2D>& texture);
        static void drawQuad(const math3D::Vector2f& position, const Ref<Texture2D>& texture);

        static void drawQuad(const math3D::Vector2f& position, const math3D::Vector2f& size, const Color& color, const math3D::Angle& angle, const Ref<SubTexture2D>& subTexture);
        static void drawQuad(const math3D::Vector2f& position, const math3D::Vector2f& size, const Color& color, const Ref<SubTexture2D>& subTexture);
        static void drawQuad(const math3D::Vector2f& position, const math3D::Vector2f& size, const math3D::Angle& angle, const Ref<SubTexture2D>& subTexture);
        static void drawQuad(const math3D::Vector2f& position, const math3D::Vector2f& size, const Ref<SubTexture2D>& subTexture);

        
        static void drawQuad(const math3D::Vector2f& position, const math3D::Vector2f& size, const Color& color, const math3D::Angle& angle);
        static void drawQuad(const math3D::Vector2f& position, const math3D::Vector2f& size, const Color& color);
    };
}