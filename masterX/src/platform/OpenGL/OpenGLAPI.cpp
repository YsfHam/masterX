#include "mxpch.hpp"
#include "OpenGLAPI.hpp"

#include <glad/glad.h>

namespace mx
{
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

    void OpenGLAPI::drawIndexed(Ref<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }
}