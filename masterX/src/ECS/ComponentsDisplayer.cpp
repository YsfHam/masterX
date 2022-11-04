#include "mxpch.hpp"
#include "ComponentsDisplayer.hpp"

namespace mx
{
    void ComponentsDisplayer::displayComponents(EntityID entity)
    {
        displayComponentsFromList<AllComponents>(entity);
    }

    template<>
    void ComponentsDisplayer::displayComponent<TagComponent>(EntityID entity)
    {
        auto& tagComponent = EntityRegistry::getComponent<TagComponent>(entity);

        ImGui::InputText("Tag", &tagComponent.Tag);
    }

    template<>
    void ComponentsDisplayer::displayComponent<Transform2DComponent>(EntityID entity)
    {
        drawComponent<Transform2DComponent>("Transform2D", entity, [](auto& transformComponent){
            ImGui::DragFloat2("Position", (float*)&transformComponent.Position);
            ImGui::DragFloat2("Size", (float*)&transformComponent.Size);
            
            float rotation = transformComponent.Rotation;
            ImGui::DragFloat("Rotation", &rotation);
            transformComponent.Rotation = rotation;
        });

    }

    template<>
    void ComponentsDisplayer::displayComponent<SpriteRendererComponent>(EntityID entity)
    {
        drawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [](auto& spriteRendererComponent){
            ImGui::ColorEdit4("Color", (float*)&spriteRendererComponent.Color); 
        });

    }
}