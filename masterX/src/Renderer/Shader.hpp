#pragma once

#include "mxpch.hpp"
#include "utils/types.hpp"
#include "math3D/math3D.hpp"
#include "Color.hpp"

namespace mx
{
    class Shader
    {
    public:
        static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragSrc);

        virtual ~Shader() = default;

        virtual void bind() = 0;

        virtual void setUniform(const std::string& name, const math3D::Matrix4f& value) = 0;
        virtual void setUniform(const std::string& name, const math3D::Matrix3f& value) = 0;
        virtual void setUniform(const std::string& name, const Color& color) = 0;
    };
}