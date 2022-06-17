#include "EditorLayer.hpp"

EditorLayer::EditorLayer()
    : m_camera(0.0f, 
    mx::Application::get().getWindow().getWidth(),
    0.0f,
    mx::Application::get().getWindow().getHeight())
{

}

void EditorLayer::onAttach()
{
    mx::FramebufferSpecification spec;
    spec.Attachements = 
    {
        mx::FramebufferAttachementFormat::RGB,
        mx::FramebufferAttachementFormat::RGB
    };
    spec.Width = mx::Application::get().getWindow().getWidth();
    spec.Height = mx::Application::get().getWindow().getHeight();

    m_framebuffer = mx::Framebuffer::Create(spec);

    mx::AssetsManager::loadAsset("face", mx::AssetLoader<mx::Texture2D>::fromFile("assets/images/awesomeface.png"));
}

void EditorLayer::onUpdate(mx::Time dt)
{
    math3D::Vector2f camPos = math3D::Vector2f::Zero;

    if (mx::Input::isKeyPressed(mx::Key::W))
        camPos.y = 1.0f;
    if (mx::Input::isKeyPressed(mx::Key::S))
        camPos.y = -1.0f;
    if (mx::Input::isKeyPressed(mx::Key::A))
        camPos.x = -1.0f;
    if (mx::Input::isKeyPressed(mx::Key::D))
        camPos.x = 1.0f;
    
    if (mx::Input::isKeyPressed(mx::Key::R))
        m_camera.rotate(5.0f);
    if (mx::Input::isKeyPressed(mx::Key::F))
        m_camera.rotate(-5.0f);
    if (camPos != math3D::Vector2f::Zero)
        m_camera.move(math3D::normalize(camPos) * 100.0f * dt);

    if (m_viewPortSize.x > 0 && m_viewPortSize.y > 0)
    {
        mx::RendererCommand::setViewport(0, 0, m_viewPortSize.x, m_viewPortSize.y);
        m_framebuffer->resize(m_viewPortSize.x, m_viewPortSize.y);
        m_camera.setProjection(0.0f, m_viewPortSize.x, 0.0f, m_viewPortSize.y);
    }
    m_framebuffer->bind();
    mx::RendererCommand::setClearColor(mx::Color::Black);
    mx::RendererCommand::clear();

    mx::Renderer2D::beginScene(m_camera);
    mx::Renderer2D::drawQuad({200.0f, 300.0f}, {100.0f, 100.0f}, mx::Color::Blue);
    mx::Renderer2D::endScene();

    m_framebuffer->unbind();
}

void EditorLayer::onImguiRender()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    auto texture = mx::AssetsManager::getAsset<mx::Texture2D>("face");
    ImGui::Begin("Viewport");
    auto viewportPanelSize = ImGui::GetContentRegionAvail();
    m_viewPortSize = {viewportPanelSize.x, viewportPanelSize.y};
    ImGui::Image((ImTextureID)(uint64_t)m_framebuffer->getColorAttachement(0), {m_viewPortSize.x, m_viewPortSize.y});
    ImGui::End();
}