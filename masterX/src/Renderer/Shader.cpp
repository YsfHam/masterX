#include "mxpch.hpp"
#include "Shader.hpp"

#include "core/Application.hpp"

#include "platform/OpenGL/OpenGLShader.hpp"

mx::Ref<mx::Shader> mx::Shader::Create(const std::string& vertexSrc, const std::string& fragSrc)
{
    switch (Application::get().getRendererAPI())
    {
        case RendererAPI::None: return nullptr;
        case RendererAPI::OpenGL: return Ref<OpenGLShader>::Create(vertexSrc, fragSrc);
    }

    MX_CORE_ASSERT(false , "Unknown Renderer API");
    return nullptr;
}