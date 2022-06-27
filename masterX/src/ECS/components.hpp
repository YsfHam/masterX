#pragma once

#include "mxpch.hpp"

#include "math3D/math3D.hpp"

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
        math3D::Vector2f Position = math3D::Vector2f::Zero;
        math3D::Vector2f Size = math3D::Vector2f::Zero;
        math3D::Angle Rotation = 0.0f;
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