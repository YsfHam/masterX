#include <masterX.hpp>
#include <core/EntryPoint.hpp>

using namespace mx;

class SandboxLayer : public Layer
{
public:
    SandboxLayer()
        : m_camera(0.0f, 800.0f, 0.0f, 600.0f)
    {
    }

    virtual void onAttach() override
    {
        MX_INFO("Hello Sandbox layer");

        AssetsManager::loadAsset("face", AssetLoader<Texture2D>::fromFile("assets/images/awesomeface.png"));
        auto tex = AssetsManager::loadAsset("character", AssetLoader<Texture2D>::fromFile("assets/images/spriteSheet.png"));

        for (int y = 0; y < 2; y++)
        {
            for (int x = 0; x < 3; x++)
                m_subTextures[y * 3 + x] = SubTexture2D::Create(tex, {(float)x, (float)y}, {172.0f, 153.0f});
        }
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

        auto faceTex = AssetsManager::getAsset<Texture2D>("face");
        faceTex->setTillingFactor(3.0f);

        RendererCommand::setClearColor({0.2f, 0.2f, 0.2f, 1.0f});
        RendererCommand::clear();

        Renderer2D::beginScene(m_camera);
        Renderer2D::drawQuad({300.0f, 150.0f}, {172.0f, 153.0f}, m_subTextures[m_drawIndex]);
        if (m_animationTimer.getElapsedTime() > m_animationDuration)
        {
            m_drawIndex = (m_drawIndex + 1) % m_subTextures.size();
            m_animationTimer.restart();
        }

        Renderer2D::endScene();
    }


    virtual void onImguiRender() override
    {
    }

private:
    Ref<VertexArray> m_vertexArray;

    Camera2D m_camera;
    std::array<Ref<SubTexture2D>, 6> m_subTextures;
    uint32_t m_drawIndex = 0;
    Timer m_animationTimer;
    Time m_animationDuration = Time::fromMiliseconds(100.0f);
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