#include "mxpch.hpp"
#include "Shader.hpp"

#include "core/Application.hpp"

#include "platform/OpenGL/OpenGLShader.hpp"

mx::Ref<mx::Shader> mx::Shader::Create(const std::string& filepath)
{
    switch (Application::get().getRendererAPI())
    {
        case RendererAPI::None: return nullptr;
        case RendererAPI::OpenGL: return Ref<OpenGLShader>::Create(filepath);
    }

    MX_CORE_ASSERT(false , "Unknown Renderer API");
    return nullptr;
}

mx::Ref<mx::Shader> mx::Shader::Create(const std::array<ShaderSource, NB_SHADER_TYPES>& shaders)
{
    switch (Application::get().getRendererAPI())
    {
        case RendererAPI::None: return nullptr;
        case RendererAPI::OpenGL: return Ref<OpenGLShader>::Create(shaders);
    }

    MX_CORE_ASSERT(false , "Unknown Renderer API");
    return nullptr;
}