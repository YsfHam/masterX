#pragma once

#include "mxpch.hpp"
#include "utils/types.hpp"
#include "Color.hpp"
#include "core/AssetsManager.hpp"
#include "core/Assert.hpp"

#include <glm/glm.hpp>


constexpr size_t NB_SHADER_TYPES = 2;

namespace mx
{
    namespace
    {
        enum class ShaderType
        {
            Vertex,
            Fragment
        };
        const char* shaderTypes[] = {
            "vertex",
            "fragment"
        };

        inline ShaderType getShaderType(const std::string& shaderTypeName)
        {
            if (shaderTypeName == "vertex")
                return ShaderType::Vertex;
            else if (shaderTypeName == "fragment")
                return ShaderType::Fragment;
            MX_CORE_ASSERT(false, "Unknown shader type {}", shaderTypeName);
            return (ShaderType)0;
        }
    }
    struct ShaderSource
    {
        std::string Source;
        ShaderType Type;
    };

    class Shader : public Asset
    {
    public:
        static Ref<Shader> Create(const std::array<ShaderSource, NB_SHADER_TYPES>& shaders);
        static Ref<Shader> Create(const std::string& filepath);

        virtual ~Shader() = default;

        virtual void bind() = 0;

        virtual void setUniform(const std::string& name, const float& value) = 0;
        virtual void setUniform(const std::string& name, const glm::vec2& value) = 0;
        virtual void setUniform(const std::string& name, const glm::vec3& value) = 0;
        virtual void setUniform(const std::string& name, const glm::vec4& value) = 0;

        virtual void setUniform(const std::string& name, float* value, uint32_t count) = 0;
        virtual void setUniform(const std::string& name, glm::vec2* value, uint32_t count) = 0;
        virtual void setUniform(const std::string& name, glm::vec3* value, uint32_t count) = 0;
        virtual void setUniform(const std::string& name, glm::vec4* value, uint32_t count) = 0;

        virtual void setUniform(const std::string& name, const glm::mat4& value) = 0;
        virtual void setUniform(const std::string& name, const glm::mat3& value) = 0;

        virtual void setUniform(const std::string& name, glm::mat4* value, uint32_t count) = 0;
        virtual void setUniform(const std::string& name, glm::mat3* value, uint32_t count) = 0;

        virtual void setUniform(const std::string& name, const int& value) = 0;
        virtual void setUniform(const std::string& name, int* value, uint32_t count) = 0;

        virtual void setUniform(const std::string& name, const Color& color) = 0;
    };
}