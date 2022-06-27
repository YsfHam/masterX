#pragma once

#include "ecs.hpp"
#include "components.hpp"

#include "Renderer/Camera2D.hpp"
#include "Renderer/Renderer2D.hpp"

namespace mx
{
    class RendererSystem : public System
    {
    public:
        void render(Camera2D& camera)
        {
            mx::Renderer2D::beginScene(camera);
            for (auto entity : m_entities)
            {
                auto& transform = mx::EntityRegistry::getComponent<Transform2DComponent>(entity);
                auto& sprite = mx::EntityRegistry::getComponent<SpriteRendererComponent>(entity);
                if (sprite.Texture == nullptr)
                    mx::Renderer2D::drawQuad(
                        transform.Position, transform.Size, sprite.Color, transform.Rotation
                        );
                else
                    mx::Renderer2D::drawQuad(
                        transform.Position, transform.Size, sprite.Color, transform.Rotation, sprite.Texture
                        );
            }

            mx::Renderer2D::endScene();
        }
    };
}