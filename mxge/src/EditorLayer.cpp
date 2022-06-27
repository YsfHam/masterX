#include "EditorLayer.hpp"


EditorLayer::EditorLayer()
    : m_editorCamera(0.0f, 
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

    m_activeScene = mx::Ref<mx::Scene>::Create();

    auto blueSquareEntity = m_activeScene->createEntity("blue square");

    auto& transformCmp = mx::EntityRegistry::addComponent<mx::Transform2DComponent>(blueSquareEntity);

    transformCmp.Position = {200.0f, 300.0f};
    transformCmp.Size = {100.0f, 100.0f};

    auto& spriteCmp = mx::EntityRegistry::addComponent<mx::SpriteRendererComponent>(blueSquareEntity);

    spriteCmp.Color = mx::Color::Blue;
    spriteCmp.Texture = mx::AssetsManager::getAsset<mx::Texture2D>("face");
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
        m_editorCamera.rotate(5.0f);
    if (mx::Input::isKeyPressed(mx::Key::F))
        m_editorCamera.rotate(-5.0f);
    if (camPos != math3D::Vector2f::Zero)
        m_editorCamera.move(math3D::normalize(camPos) * 100.0f * dt);

    if (m_viewPortSize.x > 0 && m_viewPortSize.y > 0)
    {
        mx::RendererCommand::setViewport(0, 0, m_viewPortSize.x, m_viewPortSize.y);
        m_framebuffer->resize(m_viewPortSize.x, m_viewPortSize.y);
        m_editorCamera.setProjection(0.0f, m_viewPortSize.x, m_viewPortSize.y, 0.0f);
    }
    m_framebuffer->bind();
    mx::RendererCommand::setClearColor(mx::Color::Black);
    mx::RendererCommand::clear();

    m_activeScene->renderScene(m_editorCamera);

    m_framebuffer->unbind();
}

void EditorLayer::onImguiRender()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("MXGE"))
        {
            if (ImGui::MenuItem("Close"))
            {
                mx::Application::get().exit();
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::Begin("Viewport");
    auto viewportPanelSize = ImGui::GetContentRegionAvail();
    m_viewPortSize = {viewportPanelSize.x, viewportPanelSize.y};
    ImGui::Image((ImTextureID)(uint64_t)m_framebuffer->getColorAttachement(0), {m_viewPortSize.x, m_viewPortSize.y});
    ImGui::End();

    ImGui::ShowDemoWindow();


    ImGui::Begin("Entities");
    showActiveSceneEntities();

    ImGui::Text("Hovered Entity %u", m_hoveredEntity);

    if ((m_hoveredEntity == mx::NullEntity) && ImGui::BeginPopupContextWindow("Menu Popup"))
    {
        if (ImGui::MenuItem("Add Entity"))
            m_activeScene->createEntity();
        ImGui::EndPopup();
    }

    ImGui::End();

    ImGui::Begin("Entity components");
    if (m_selectedEntity != mx::NullEntity)
    {
        if (ImGui::BeginPopupContextWindow("Components Menu"))
        {
            if (ImGui::MenuItem("Transform2D component"))
            {
                if (!mx::EntityRegistry::hasComponent<mx::Transform2DComponent>(m_selectedEntity))
                    mx::EntityRegistry::addComponent<mx::Transform2DComponent>(m_selectedEntity);
            }
            if (ImGui::MenuItem("Sprite renderer component"))
            {
                if (!mx::EntityRegistry::hasComponent<mx::SpriteRendererComponent>(m_selectedEntity))
                    mx::EntityRegistry::addComponent<mx::SpriteRendererComponent>(m_selectedEntity);
            }

            ImGui::EndPopup();
        }

        if (ImGui::Button("Add component"))
            ImGui::OpenPopup("Components Menu");

        m_componentsDisplayer.displayComponents(m_selectedEntity);
    }
    ImGui::End();

}

void EditorLayer::showActiveSceneEntities()
{
    ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    
    m_hoveredEntity = mx::NullEntity;

    for (auto& entity  : *m_activeScene)
    {
        ImGuiTreeNodeFlags nodeFlags = baseFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        if (m_selectedEntity == entity)
            nodeFlags |= ImGuiTreeNodeFlags_Selected;
        auto entityName = mx::EntityRegistry::getComponent<mx::TagComponent>(entity).Tag.c_str();
        ImGui::TreeNodeEx(reinterpret_cast<void*>(entity), nodeFlags, "%s", entityName);

        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
            m_selectedEntity = entity;
        if (ImGui::IsItemHovered())
            m_hoveredEntity = entity;

    }
}