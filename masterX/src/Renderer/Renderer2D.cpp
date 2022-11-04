#include "mxpch.hpp"
#include "Renderer2D.hpp"

#include "Renderer/QuadBatch.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/Buffer.hpp"

#include "utils/memory.hpp"

struct QuadVertex
{
    glm::vec3 Pos = glm::vec3(0.0f);
    glm::vec2 TexCoords = glm::vec2(0.0f);
    mx::Color Color = mx::Color::White;
    float TextureIndex = 0.f;
    float TillingFactor = 1.0f;
};

struct Tex2DData
{
    mx::Ref<mx::Texture2D> Texture;
    uint32_t TextureIndex;
};

struct RendererData
{
    static const uint32_t MaxQuads = 20000;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;

    static const uint32_t TexturesSlots = 16;
    
    std::unordered_map<uint32_t, Tex2DData> Textures;
    uint32_t NbTextures = 0;
    mx::Ref<mx::Texture2D> DefaultTexture;
    glm::vec2 TextureCoords[4];

    mx::QuadBatch<QuadVertex, MaxQuads> QuadRenderBatch;

    mx::Ref<mx::Shader> QuadShader;

    glm::vec4 vertices[4];

    mx::Ref<mx::VertexArray> VertexArray;
    mx::Ref<mx::IndexBuffer> IndexBuffer;

    RendererData()
    : vertices{
        { 0.f, 1.f,  0.0f, 1.0f},
        { 1.f, 1.f,  0.0f, 1.0f},
        { 1.f, 0.f,  0.0f, 1.0f},
        { 0.f, 0.f,  0.0f, 1.0f}
    },
    TextureCoords{
        {0.0f, 1.0f},
        {1.0f, 1.0f},
        {1.0f, 0.0f},
        {0.0f, 0.0f}
    }
    {
    }
};

static RendererData *s_data = nullptr;

static void addQuadToBatch(QuadVertex *vertices, const glm::mat4& transform, const mx::Color& color, float textureIndex, float tillingFactor, const glm::vec2* texCoords)
{
    vertices[0].Pos = transform * s_data->vertices[0];
    vertices[1].Pos = transform * s_data->vertices[1];
    vertices[2].Pos = transform * s_data->vertices[2];
    vertices[3].Pos = transform * s_data->vertices[3];

    vertices[0].TexCoords = texCoords[0];
    vertices[1].TexCoords = texCoords[1];
    vertices[2].TexCoords = texCoords[2];
    vertices[3].TexCoords = texCoords[3];


    vertices[0].Color = color;
    vertices[1].Color = color;
    vertices[2].Color = color;
    vertices[3].Color = color;

    vertices[0].TextureIndex = textureIndex;
    vertices[1].TextureIndex = textureIndex;
    vertices[2].TextureIndex = textureIndex;
    vertices[3].TextureIndex = textureIndex;

    vertices[0].TillingFactor = tillingFactor;
    vertices[1].TillingFactor = tillingFactor;
    vertices[2].TillingFactor = tillingFactor;
    vertices[3].TillingFactor = tillingFactor;
}

static void FlushTextures()
{
    for (auto&[id, texData] : s_data->Textures)
        texData.Texture->bind(texData.TextureIndex);

    s_data->Textures.clear();
    s_data->NbTextures = 0;
}

void mx::Renderer2D::init() 
{
    s_data = MX_ALLOCATE(RendererData);

    // init quad shader
    s_data->QuadShader = AssetsManager::loadAsset<Shader>("QuadShader", AssetLoader<Shader>::fromFile("assets/shaders/QuadShader.glsl"));
    s_data->QuadShader->bind();
    for (int i(0); i < s_data->TexturesSlots; i++)
    {
        std::string uniform = "u_textures[" + std::to_string(i) + "]";
        s_data->QuadShader->setUniform(uniform, i);
    }
    // give the shader to the batch for drawing
    s_data->QuadRenderBatch.setShader(s_data->QuadShader);

    // load default white texture used for drawing quads with flat color
    s_data->DefaultTexture = AssetsManager::loadAsset<Texture2D>("whiteTexture", AssetLoader<Texture2D>::fromFile("assets/images/whiteTexture.png"));
    // init vertex array
    s_data->VertexArray = mx::VertexArray::Create();
    
    s_data->VertexArray->bind();

    // add the batch vertex buffer to the vertex array
    s_data->QuadRenderBatch.attachToVertexArray(s_data->VertexArray, {
        {ShaderDataType::Vec3, "a_pos"},
        {ShaderDataType::Vec2, "a_texPos"},
        {ShaderDataType::Vec4, "a_color"},
        {ShaderDataType::Float, "a_texIndex"},
        {ShaderDataType::Float, "a_tillingFactor"}
    });


    // init index/element buffer
    uint32_t indices[RendererData::MaxIndices];
    uint32_t offset = 0;
    for (int i(0); i < RendererData::MaxIndices; i += 6)
    {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;
        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;
        offset += 4;
    }

    auto indexBuffer = IndexBuffer::Create(indices, RendererData::MaxIndices);
    s_data->VertexArray->setIndexBuffer(indexBuffer);

    s_data->VertexArray->unbind();
}

void mx::Renderer2D::shutdown()
{
    MX_FREE(s_data);
}

void mx::Renderer2D::beginScene(Camera2D& camera)
{
    s_data->QuadShader->bind();
    s_data->QuadShader->setUniform("u_pv", camera.getPV());
}
        
void mx::Renderer2D::endScene()
{
    if (s_data->NbTextures > 0)
        FlushTextures();
    s_data->QuadRenderBatch.flush();
}

void mx::Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color, float angle, const Ref<Texture2D>& texture)
{
    if (s_data->NbTextures == s_data->TexturesSlots)
    {
        FlushTextures();
        s_data->QuadRenderBatch.flush();
    }

    glm::mat4 model = glm::mat4(1.0f);   

    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(size, 0.0f));

    uint32_t textureIndex = 0;
    auto it = s_data->Textures.find(texture->getID());
    if (it == s_data->Textures.end())
    {
        textureIndex = s_data->NbTextures++;
        s_data->Textures[texture->getID()] = {texture, textureIndex};
    }
    else
        textureIndex = it->second.TextureIndex;

    s_data->QuadRenderBatch.add(addQuadToBatch, model, color, (float)textureIndex, texture->getTillingFactor(), s_data->TextureCoords);
}

void mx::Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color, const Ref<Texture2D>& texture)
{
    drawQuad(position, size, color, 0.0f, texture);
}

void mx::Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, float angle, const Ref<Texture2D>& texture)
{
    drawQuad(position, size, Color::White, angle, texture);
}

void mx::Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
{
    drawQuad(position, size, 0.0f, texture);
}

void mx::Renderer2D::drawQuad(const glm::vec2& position, const Ref<Texture2D>& texture)
{
    glm::vec2 size = {
    static_cast<float>(texture->getWidth()), 
    static_cast<float>(texture->getHeight())
    };
    drawQuad(position, size, texture);
}

void mx::Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color, float angle, const Ref<SubTexture2D>& subTexture)
{
    if (s_data->NbTextures == s_data->TexturesSlots)
    {
        FlushTextures();
        s_data->QuadRenderBatch.flush();
    }

    glm::mat4 model = glm::mat4(1.0f);   

    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(size, 0.0f));

    auto texture = subTexture->getTexture();
    uint32_t textureIndex = 0;
    auto it = s_data->Textures.find(texture->getID());
    if (it == s_data->Textures.end())
    {
        textureIndex = s_data->NbTextures++;
        s_data->Textures[texture->getID()] = {texture, textureIndex};
    }
    else
        textureIndex = it->second.TextureIndex;

    s_data->QuadRenderBatch.add(addQuadToBatch, model, color, (float)textureIndex, texture->getTillingFactor(), subTexture->getTextureCoords());
}

void mx::Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color, const Ref<SubTexture2D>& subTexture)
{
    drawQuad(position, size, color, 0.0f, subTexture);
}

void mx::Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, float angle, const Ref<SubTexture2D>& subTexture)
{
    drawQuad(position, size, Color::White, angle, subTexture);
}

void mx::Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture)
{
    drawQuad(position, size, Color::White, 0.0f, subTexture);
}


// Solid color drawing
void mx::Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color, float angle)
{
    drawQuad(position, size, color, angle, s_data->DefaultTexture);
}

void mx::Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Color& color) 
{
    drawQuad(position, size, color, 0.0f);
}

