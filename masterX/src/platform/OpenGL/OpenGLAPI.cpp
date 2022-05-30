#include "mxpch.hpp"
#include "OpenGLAPI.hpp"

#include <glad/glad.h>

namespace mx
{
    OpenGLAPI::OpenGLAPI()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLAPI::setClearColor(const Color& clearColor)
    {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        m_clearFlags |= GL_COLOR_BUFFER_BIT;
    }
    
    void OpenGLAPI::clear()
    {
        glClear(m_clearFlags);
        m_clearFlags = 0;
    }

    void OpenGLAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLAPI::drawIndexed(Ref<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }
}