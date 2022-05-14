#pragma once

#include "RendererCommand.hpp"

namespace mx
{
    class Renderer
    {
    public:
        static void beginScene();
        static void endScene();

        static void submit(Ref<VertexArray>& vertexArray);
    };
}