#pragma once

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

        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color, float angle, const Ref<Texture2D>& texture);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color, const Ref<Texture2D>& texture);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, float angle, const Ref<Texture2D>& texture);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void drawQuad(const glm::vec2& position, const Ref<Texture2D>& texture);

        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color, float angle, const Ref<SubTexture2D>& subTexture);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color, const Ref<SubTexture2D>& subTexture);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, float angle, const Ref<SubTexture2D>& subTexture);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture);

        
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color, float angle);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color);
    };
}