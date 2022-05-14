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
    private:
        bool compileShader(const std::string& shaderSource, GLenum shaderType, RendererID& shaderID, std::vector<GLchar>& infoLog);
    private:
        RendererID m_shaderID;
    };
}