#include <masterX.hpp>
#include <core/EntryPoint.hpp>

using namespace mx;

class SandboxLayer : public Layer
{
    virtual void onAttach() override
    {
        MX_INFO("Hello Sandbox layer");

        std::string vertexShader = R"(
            #version 330 core
            layout (location = 0) in vec3 a_pos;

            uniform mat4 u_model;

            void main()
            {
                gl_Position = u_model * vec4(a_pos, 1.0);
            }
        )";

        std::string fragmentShader = R"(
            #version 330 core

            out vec4 color;

            void main()
            {
                color = vec4(1.0);
            }
        )";

        m_shader = Shader::Create(vertexShader, fragmentShader);

        float vertices[] = {
            -0.5f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        m_vertexArray = VertexArray::Create();
        auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        
        BufferLayout layout = {
            {ShaderDataType::Vec3, "a_pos"}
        };

        vertexBuffer->setLayout(layout);

        m_vertexArray->addVertexBuffer(vertexBuffer);

        uint32_t indices[] = {
            0, 1, 2
        };

        auto indexBuffer = IndexBuffer::Create(indices, 3);
        m_vertexArray->setIndexBuffer(indexBuffer);

        m_vertexArray->unbind();
    }

    virtual void onDetach() override
    {
        MX_INFO("Hello Sandbox layer leaving");
    }

    virtual void onUpdate() override
    {
        RendererCommand::setClearColor({0.2f, 0.3f, 0.1f, 1.0f});
        RendererCommand::clear();

        math3D::Matrix4f model = math3D::Matrix4f::Identity;
        model = math3D::translate(model, m_translation);

        m_shader->bind();
        m_shader->setUniform("u_model", model);
        Renderer::beginScene();
        Renderer::submit(m_vertexArray);
        Renderer::endScene();
    }

    virtual bool onWindowClose(WindowCloseEvent& e) override
    {
        MX_WARN("Are you trying to leave !!!");

        return false;
    }

    virtual bool onKeyPressed(KeyPressedEvent& e) override
    {

        return true;
    }

    virtual void onEventReceive(Event& e) override
    {
    }

    virtual void onImguiRender() override
    {
        ImGui::InputFloat3("inputFloat", (float*)&m_translation);
    }

private:
    Ref<VertexArray> m_vertexArray;
    Ref<Shader> m_shader;

    math3D::Vector3f m_translation = math3D::Vector3f::Zero;

};

class SandboxApp : public Application
{
public:
    SandboxApp(const AppSettings& settings)
        : Application(settings)
    {
        MX_INFO("Hello World");

        pushLayer(Ref<SandboxLayer>::Create());
    }
};

mx::Ref<mx::Application> mx::createApplication(const CommandLineArgs& args)
{
    AppSettings settings;
    settings.WinProperties.Title = "Sandbox App";
    settings.WinAPI = WindowAPI::GLFW;
    settings.GraphicsAPI = RendererAPI::OpenGL;
    return Ref<SandboxApp>::Create(settings);
}