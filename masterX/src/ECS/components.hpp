#pragma once

#include "mxpch.hpp"

#include "Renderer/Color.hpp"
#include "Renderer/Texture.hpp"

namespace mx
{
    struct TagComponent
    {
        std::string Tag;
    };

    struct Transform2DComponent
    {
        glm::vec2 Position = glm::vec2(0.0f);
        glm::vec2 Size = glm::vec2(0.0f);
        float Rotation = 0.0f;
    };

    struct SpriteRendererComponent
    {
        mx::Color Color = mx::Color::White;
        mx::Ref<mx::Texture2D> Texture = nullptr;
    };

    template<typename ...Components>
    struct ComponentsList {};

    template<typename First, typename ...Rest>
    struct ComponentsList<First, Rest ...>
    {
        using FirstCmp = First;
        using RestCmps = ComponentsList<Rest...>;

        constexpr static bool valid = true;
    };

    template<>
    struct ComponentsList<>
    {
        using FirstCmp = void;
        using RestCmps = void;

        constexpr static bool valid = false;
    };


    using AllComponents = ComponentsList<
        TagComponent,
        Transform2DComponent,
        SpriteRendererComponent
    >;
}