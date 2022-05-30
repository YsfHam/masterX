#include "mxpch.hpp"
#include "OpenGLVertexArray.hpp"

#include <glad/glad.h>

static GLenum OpenGLShaderDataType(mx::ShaderDataType::Type dataType)
{
    switch (dataType)
        {
            case mx::ShaderDataType::Float:  return GL_FLOAT;
            case mx::ShaderDataType::Vec2:   return GL_FLOAT;
            case mx::ShaderDataType::Vec3:   return GL_FLOAT;
            case mx::ShaderDataType::Vec4:   return GL_FLOAT;
            case mx::ShaderDataType::Mat3:   return GL_FLOAT;
            case mx::ShaderDataType::Mat4:   return GL_FLOAT;

            case mx::ShaderDataType::Int:     return GL_INT;
            case mx::ShaderDataType::IVec2:   return GL_INT;
            case mx::ShaderDataType::IVec3:   return GL_INT;
            case mx::ShaderDataType::IVec4:   return GL_INT;

            case mx::ShaderDataType::Bool: return GL_INT;

            default: MX_CORE_ASSERT(false, "Unknown data type");
        }

    return 0;
}

mx::OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &m_vertexArrayID);
}

mx::OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_vertexArrayID);
}

void mx::OpenGLVertexArray::bind()
{
    glBindVertexArray(m_vertexArrayID);
}

void mx::OpenGLVertexArray::unbind()
{
    glBindVertexArray(0);
}

void mx::OpenGLVertexArray::addVertexBuffer(Ref<VertexBuffer> vertexBuffer)
{
    MX_CORE_ASSERT(!vertexBuffer->getLayout().isEmpty(), "Vertex buffer has no layout");
    glBindVertexArray(m_vertexArrayID);

    vertexBuffer->bind();
    const auto& layout = vertexBuffer->getLayout();

    uint32_t index = 0;
    for (const auto& element : layout)
    {
        glVertexAttribPointer(index, element.DataType.getComponentCount(),
         OpenGLShaderDataType(element.DataType.DataType), 
         element.Normalized ? GL_TRUE : GL_FALSE, 
         layout.getStride(), (void*)element.Offset);
         
        glEnableVertexAttribArray(index);
        index++;
    }
    
    m_vertexBuffers.push_back(vertexBuffer);
}

void mx::OpenGLVertexArray::setIndexBuffer(Ref<IndexBuffer> indexBuffer)
{
    glBindVertexArray(m_vertexArrayID);
    indexBuffer->bind();
    m_indexBuffer = indexBuffer;
}

mx::Ref<mx::VertexBuffer>& mx::OpenGLVertexArray::getVertexBuffer(uint32_t index)
{
    MX_CORE_ASSERT(index < m_vertexBuffers.size(), "Index out of bound");
    return m_vertexBuffers[index];
}
        
mx::Ref<mx::IndexBuffer>& mx::OpenGLVertexArray::getIndexBuffer()
{
    return m_indexBuffer;
}