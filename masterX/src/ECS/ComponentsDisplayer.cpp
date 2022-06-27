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
        auto& transformComponent = EntityRegistry::getComponent<Transform2DComponent>(entity);

        ImGui::DragFloat2("Position", (float*)&transformComponent.Position);
        ImGui::DragFloat2("Size", (float*)&transformComponent.Size);
        ImGui::DragFloat("Rotation", (float*)&transformComponent.Rotation);
    }

    template<>
    void ComponentsDisplayer::displayComponent<SpriteRendererComponent>(EntityID entity)
    {
        auto& spriteRendererComponent = EntityRegistry::getComponent<SpriteRendererComponent>(entity);

        ImGui::ColorEdit4("Color", (float*)&spriteRendererComponent.Color);
    }
}