#pragma once

#include "Renderer/Shader.hpp"

#include <glad/glad.h>

namespace mx
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragSrc);
        ~OpenGLShader() { glDeleteProgram(m_shaderID); }

        virtual void bind() override;
        virtual void setUniform(const std::string& name, const math3D::Matrix4f& value) override;
    private:
        bool compileShader(const std::string& shaderSource, GLenum shaderType, RendererID& shaderID, std::vector<GLchar>& infoLog);
    private:
        RendererID m_shaderID;
    };
}