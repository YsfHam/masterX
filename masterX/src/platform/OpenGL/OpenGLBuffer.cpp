#include "mxpch.hpp"
#include "OpenGLBuffer.hpp"

mx::OpenGLVertexBuffer::OpenGLVertexBuffer(void *vertices, uint32_t size)
{
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ARRAY_BUFFER, size , vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

mx::OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ARRAY_BUFFER, size , nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

mx::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_bufferID);
}

void mx::OpenGLVertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}

void mx::OpenGLVertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void mx::OpenGLVertexBuffer::addSubData(void *vertices, uint32_t size,  uint32_t offset)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
}

// index buffer impl


mx::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count)
    : m_count(count)
{
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

mx::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_bufferID);
}

void mx::OpenGLIndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void mx::OpenGLIndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

