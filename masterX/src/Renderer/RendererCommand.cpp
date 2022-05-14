#include "mxpch.hpp"
#include "RendererCommand.hpp"

#include "core/Application.hpp"

#include "platform/OpenGL/OpenGLAPI.hpp"

mx::Scope<mx::RendererCommandsAPI> mx::RendererCommand::s_rendererAPI;


void mx::RendererCommand::init()
{
    switch (Application::get().getRendererAPI())
    {
        case RendererAPI::None: s_rendererAPI = nullptr; break;
        case RendererAPI::OpenGL: s_rendererAPI = Scope<OpenGLAPI>::Create(); break;
    }

}

