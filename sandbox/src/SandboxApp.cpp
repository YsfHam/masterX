#include <masterX.hpp>
#include <core/EntryPoint.hpp>

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

    bool UseTex = false;
};

class SandboxLayer : public Layer
{
public:
    SandboxLayer()
        : m_camera(0.0f, 800.0f, 0.0f, 600.0f)
    {
        srand(time(nullptr));

        AssetsManager::loadAsset("face", AssetLoader<Texture2D>::fromFile("assets/images/awesomeface.png"));
    }

    virtual void onAttach() override
    {
        MX_INFO("Hello Sandbox layer");
    }

    virtual void onDetach() override
    {
        MX_INFO("Hello Sandbox layer leaving");
    }

    virtual bool onWindowFramebufferResize(WindowFramebufferResizeEvent& e) override
    {
        m_camera.setProjection(0, e.getWidth(), 0, e.getHeight());
        return true;
    }

    virtual void onUpdate(Time dt) override
    {
        if (m_nbFrames == 0)
        {
            m_delta = m_deltaMean / m_maxFrames;
            m_deltaMean = 0.0f;
        }
        else
        {
            m_deltaMean = m_deltaMean + dt;
        }
        m_nbFrames = (m_nbFrames + 1) % m_maxFrames;

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

        Renderer2D::beginScene(m_camera);

        for (auto& quad : m_quads)
        {
            if (!quad.UseTex)
            {
                Renderer2D::drawQuad(quad.Pos, quad.Size, quad.Color, m_angle);
            }   
            else
            {
                Renderer2D::drawQuad(quad.Pos, quad.Size, quad.Color, m_angle, AssetsManager::getAsset<Texture2D>("face"));
            }
        }   

        Renderer2D::endScene();
    }

    virtual void onImguiRender() override
    {
        ImGui::Begin("Control panel");
        ImGui::Text("allocated memory %f", MemTracker::getAllocatedMemSize() / 1024.0f);
        ImGui::Text("Freed memory %f", MemTracker::getFreedMemSize() / 1024.0f);
        ImGui::Text("memory difference %zu", MemTracker::getAllocatedMemSize() - MemTracker::getFreedMemSize());
        ImGui::Text("Allocations number %u", MemTracker::getAllocationsNumber());
        ImGui::Text("Quads number : %zu", m_quads.size());
        ImGui::Text("Draw calls : %u", Statistics::data.DrawCalls);
        ImGui::Text("delta time %f", m_delta.miliseconds());
        ImGui::Text("fps %f", 1.0f / m_delta.seconds());
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
                int random = randomBetween(0, 100);
                if (random > 50)
                    quad.UseTex = true;
                
                MX_TRACE("{}, {}", random, quad.UseTex);

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
    //Ref<Shader> m_shader;

    float m_angle = 0.0f;
    float m_rotationSpeed = 0.0f;

    int quadsToCreate = 0;

    Camera2D m_camera;

    Time m_delta;
    Time m_deltaMean;
    uint32_t m_nbFrames = 0;
    uint32_t m_maxFrames = 100;


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
    settings.args = args;
    return Ref<SandboxApp>::Create(settings);
}