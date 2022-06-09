#pragma once

#include "mxpch.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/VertexArray.hpp"
#include "RendererCommand.hpp"
#include "Shader.hpp"

#include "utils/profiling.hpp"

namespace mx
{
    template<typename Vertex, uint32_t MaxQuads>
    class QuadBatch
    {
    public:
        QuadBatch()
            : m_vertexBuffer(VertexBuffer::Create(MaxVertices * sizeof(Vertex))),
            m_verticesBufferPtr(m_vertices.data()),
            m_quadsNumber(0)
        {

        }

        template <typename F, typename ...Args>
        void add(F func, Args&& ...args)
        {
            if (m_quadsNumber == MaxQuads)
                flush();
            func(m_verticesBufferPtr, std::forward<Args>(args)...);
            m_verticesBufferPtr += 4;
            m_quadsNumber++;
        }

        void flush()
        {
            if (m_quadsNumber == 0)
                return;
            m_vertexBuffer->bind();
            m_vertexBuffer->addSubData(m_vertices.data(), sizeof(Vertex) * getVerticesNumber(), 0);
            m_vertexBuffer->unbind();
            
            m_shader->bind();
            m_vertexArray->bind();
            RendererCommand::drawIndexed(m_vertexArray, getIndicesNumber());
            m_vertexArray->unbind();

            m_verticesBufferPtr = m_vertices.data(); 
            m_quadsNumber = 0;

            Statistics::data.DrawCalls++;
        }

        void attachToVertexArray(Ref<VertexArray>& vertexArray, const BufferLayout& layout)
        {
            m_vertexBuffer->setLayout(layout);
            vertexArray->addVertexBuffer(m_vertexBuffer);
            m_vertexArray = vertexArray;
        }

        void setShader(const Ref<Shader> shader)
        {
            m_shader = shader;
        }

        uint32_t getQuadsNumber() const { return m_quadsNumber; }
        uint32_t getVerticesNumber() const { return m_quadsNumber * 4; }
        uint32_t getIndicesNumber() const { return m_quadsNumber * 6; }
        
    public:
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;
    private:
        Ref<VertexBuffer> m_vertexBuffer;
        Ref<VertexArray> m_vertexArray;

        std::array<Vertex, MaxQuads * 4> m_vertices;
        Vertex *m_verticesBufferPtr;

        uint32_t m_quadsNumber;

        Ref<Shader> m_shader;

    };
}