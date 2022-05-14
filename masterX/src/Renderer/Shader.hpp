#pragma once

#include "mxpch.hpp"
#include "utils/types.hpp"

namespace mx
{
    class Shader
    {
    public:
        static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragSrc);

        virtual ~Shader() = default;

        virtual void bind() = 0;
    };
}