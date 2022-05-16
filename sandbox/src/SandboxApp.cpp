#include <masterX.hpp>
#include <core/EntryPoint.hpp>
#include <chrono>
using namespace mx;

static int randomBetween(int a, int b)
{
    return rand() % (b - a + 1) + a;
}


struct Quad
{
    math3D::Vector2f Pos = math3D::Vector2f::Zero;
    math3D::Vector2f Size = math3D::Vector2f(1.0f, 1.0f);

    RGBA8Color Color = Color::White;


};

class SandboxLayer : public Layer
{
public:
    SandboxLayer()
        : m_camera(0.0f, 800.0f, 0.0f, 600.0f)
    {
        srand(time(nullptr));
    }

    virtual void onAttach() override
    {
        MX_INFO("Hello Sandbox layer");

        std::string vertexShader = R"(
            #version 330 core
            layout (location = 0) in vec2 a_pos;

            uniform mat3 u_model;
            uniform mat3 u_pv;

            void main()
            {
                vec3 position = u_pv * u_model * vec3(a_pos, 1.0);
                gl_Position = vec4(position.xy, 0.0, 1.0);
            }
        )";

        std::string fragmentShader = R"(
            #version 330 core

            out vec4 color;

            uniform vec4 u_color;

            void main()
            {
                color = u_color;
            }
        )";

        m_shader = Shader::Create(vertexShader, fragmentShader);

        float vertices[] = {
            -0.5f, 0.5f, 
            0.5f, 0.5f,
            0.5f, -0.5f,
            -0.5f, -0.5f,
        };

        m_vertexArray = VertexArray::Create();

        auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        
        BufferLayout layout = {
            {ShaderDataType::Vec2, "a_pos"}
        };

        vertexBuffer->setLayout(layout);

        m_vertexArray->addVertexBuffer(vertexBuffer);

        uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_vertexArray->setIndexBuffer(indexBuffer);

        m_vertexArray->unbind();

        math3D::Vector4f v(2.0f, 3.0f, 1.0f, 0.0f);
        MX_INFO(v.xy.toVector());
    }

    virtual void onDetach() override
    {
        MX_INFO("Hello Sandbox layer leaving");
    }

    virtual void onUpdate(float dt) override
    {
        m_angle += m_rotationSpeed;

        math3D::Vector2f camPos = math3D::Vector2f::Zero;

        if (Input::isKeyPressed(Key::W))
            camPos.y = -5.0f;
        if (Input::isKeyPressed(Key::S))
            camPos.y = 5.0f;
        if (Input::isKeyPressed(Key::A))
            camPos.x = -5.0f;
        if (Input::isKeyPressed(Key::D))
            camPos.x = 5.0f;
        
        if (Input::isKeyPressed(Key::R))
            m_camera.rotate(5.0f);
        if (Input::isKeyPressed(Key::F))
            m_camera.rotate(-5.0f);

        m_camera.move(camPos);

        RendererCommand::setClearColor({0.2f, 0.2f, 0.2f, 1.0f});
        RendererCommand::clear();

        m_shader->bind();
        m_shader->setUniform("u_pv", m_camera.getPV());

        Renderer::beginScene();

        for (Quad& quad : m_quads)
        {
            math3D::Matrix3f model = math3D::Matrix3f::Identity;
            model = math3D::translate2D(model, quad.Pos);
            model = math3D::rotate2D(model, m_angle);
            model = math3D::scale2D(model, quad.Size);
            m_shader->setUniform("u_model", model);
            m_shader->setUniform("u_color", quad.Color);
            Renderer::submit(m_vertexArray);
        }

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

    virtual bool onMouseScrolled(MouseScrolledEvent& e) override
    {
        return false;
    }

    virtual void onEventReceive(Event& e) override
    {
    }

    virtual void onImguiRender() override
    {
        ImGui::Begin("Control panel");
        ImGui::SliderFloat("rotation speed", &m_rotationSpeed, 0.0f, 100.0f);
        if (ImGui::InputInt("Quads to create", &quadsToCreate))
        {
            for (int i = 0; i < quadsToCreate; i++)
            {
                Quad quad;
                quad.Size.x = randomBetween(30, 100);
                quad.Size.y = randomBetween(30, 100);

                auto halfSize = quad.Size / 2.0f;

                quad.Pos.x = randomBetween(halfSize.x, 800 - halfSize.x);
                quad.Pos.y = randomBetween(halfSize.y, 600 - halfSize.y);

                quad.Color.r = randomBetween(0, 255);
                quad.Color.g = randomBetween(0, 255);
                quad.Color.b = randomBetween(0, 255);

                m_quads.push_back(quad);
            }
            quadsToCreate = 0;
        }
        int i = 0;
        for (Quad& quad: m_quads)
        {
            auto quadName = "Quad " + std::to_string(++i);
            ImGui::Text("%s", quadName.c_str());
            ImGui::DragFloat2("Position", (float*)&quad.Pos);
            ImGui::DragFloat2("Size", (float*)&quad.Size);
            int colors[] = {
                quad.Color.r, quad.Color.g, quad.Color.b
            };
            ImGui::DragInt3("Color", colors);
        }

        ImGui::End();
    }

private:
    Ref<VertexArray> m_vertexArray;
    Ref<Shader> m_shader;

    float m_angle = 0.0f;
    float m_rotationSpeed = 0.0f;

    int quadsToCreate = 0;

    Camera2D m_camera;


    std::vector<Quad> m_quads;
    
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
    settings.WinProperties.Resizable = false;
    settings.WinAPI = WindowAPI::GLFW;
    settings.GraphicsAPI = RendererAPI::OpenGL;
    return Ref<SandboxApp>::Create(settings);
}