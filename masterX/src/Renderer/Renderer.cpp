#include "mxpch.hpp"
#include "Renderer.hpp"

namespace mx
{
    void Renderer::beginScene()
    {

    }
    
    void Renderer::endScene()
    {

    }

    void Renderer::submit(Ref<VertexArray>& vertexArray)
    {
        vertexArray->bind();
        RendererCommand::drawIndexed(vertexArray);
    }
}