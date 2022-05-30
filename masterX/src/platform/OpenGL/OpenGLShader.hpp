#pragma once

#include "Renderer/Shader.hpp"

#include <glad/glad.h>

namespace mx
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::array<ShaderSource, NB_SHADER_TYPES>& shaders);
        OpenGLShader(const std::string& filepath);

        ~OpenGLShader() { glDeleteProgram(m_rendererID); }

        virtual void bind() override;

        virtual std::string getName() const override { return m_name; }

        virtual void setUniform(const std::string& name, const float& value) override;
        virtual void setUniform(const std::string& name, const math3D::Vector2f& value) override;
        virtual void setUniform(const std::string& name, const math3D::Vector3f& value) override;
        virtual void setUniform(const std::string& name, const math3D::Vector4f& value) override;

        virtual void setUniform(const std::string& name, float* value, uint32_t count) override;
        virtual void setUniform(const std::string& name, math3D::Vector2f* value, uint32_t count) override;
        virtual void setUniform(const std::string& name, math3D::Vector3f* value, uint32_t count) override;
        virtual void setUniform(const std::string& name, math3D::Vector4f* value, uint32_t count) override;

        virtual void setUniform(const std::string& name, const math3D::Matrix4f& value) override;
        virtual void setUniform(const std::string& name, const math3D::Matrix3f& value) override;

        virtual void setUniform(const std::string& name, math3D::Matrix4f* value, uint32_t count) override;
        virtual void setUniform(const std::string& name, math3D::Matrix3f* value, uint32_t count) override;

        virtual void setUniform(const std::string& name, const int& value) override;
        
        virtual void setUniform(const std::string& name, int* value, uint32_t count) override;

        virtual void setUniform(const std::string& name, const Color& color) override;
    private:
        bool compileShader(const std::string& shaderSource, GLenum shaderType, GLuint& shaderID, std::vector<GLchar>& infoLog);
        std::string readFile(const std::string& filepath);
        std::array<ShaderSource, NB_SHADER_TYPES> preProcess(const std::string& source);
        void compile(const std::array<ShaderSource, NB_SHADER_TYPES>& shaders);

    private:
        RendererID m_rendererID;

        std::string m_name;
    };
}