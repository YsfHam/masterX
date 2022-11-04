#include "EditorLayer.hpp"


EditorLayer::EditorLayer()
    : m_editorCamera(
        0.0f,
        mx::Application::get().getWindow().getWidth(), 
        0.0f,
        mx::Application::get().getWindow().getHeight()
    )
{

}

void EditorLayer::onAttach()
{
    mx::FramebufferSpecification spec;
    spec.Attachements = 
    {
        mx::FramebufferAttachementFormat::RGB
    };
    spec.Width = mx::Application::get().getWindow().getWidth();
    spec.Height = mx::Application::get().getWindow().getHeight();


    m_framebuffer = mx::Framebuffer::Create(spec);

    mx::AssetsManager::loadAsset("face", mx::AssetLoader<mx::Texture2D>::fromFile("assets/images/awesomeface.png"));

    m_activeScene = mx::Ref<mx::Scene>::Create();

    auto entity = m_activeScene->createEntity();
    auto& transform = mx::EntityRegistry::addComponent<mx::Transform2DComponent>(entity);
    transform.Position = {0.f, 0.0f};
    transform.Size = {100.0f, 100.0f};

    mx::EntityRegistry::addComponent<mx::SpriteRendererComponent>(entity);

}

void EditorLayer::onUpdate(mx::Time dt)
{
    auto& spec = m_framebuffer->getSpecification();
    if (m_viewPortSize.x > 0.0f && m_viewPortSize.y > 0.0f && 
    (m_viewPortSize.x != spec.Width || m_viewPortSize.y != spec.Height))
    {
        mx::RendererCommand::setViewport(0, 0, m_viewPortSize.x, m_viewPortSize.y);
        m_framebuffer->resize(m_viewPortSize.x, m_viewPortSize.y);
        m_editorCamera.setProjection(0.0f, m_viewPortSize.x, m_viewPortSize.y, 0.0f);
    }
    if (mx::Input::isKeyPressed(mx::Key::LeftAlt))
    {
        auto[mousePosX, mousePosY] = mx::Input::getMousePos();

        auto mousePos = glm::vec2(-mousePosX, -mousePosY);
        m_mouseDragDelta = mousePos - m_mouseInitialPosition;
        m_mouseInitialPosition = mousePos;
    }

    if (m_viewPortOnFocus)
    {
        if (mx::Input::isMouseButtonPressed(mx::Mouse::ButtonLeft))
            m_editorCamera.move(m_mouseDragDelta);
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

    
    showMainMenuBar();

    showViewport();

    showEntitiesWindow();

    showCurrentEntityComponents();
}

void EditorLayer::showActiveSceneEntities()
{
    ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    
    m_hoveredEntity = mx::NullEntity;

    std::unordered_set<mx::EntityID> entitiesToDelete;

    for (auto& entity  : *m_activeScene)
    {
        ImGuiTreeNodeFlags nodeFlags = baseFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        if (m_selectedEntity == entity)
            nodeFlags |= ImGuiTreeNodeFlags_Selected;
        auto entityName = mx::EntityRegistry::getComponent<mx::TagComponent>(entity).Tag.c_str();
        ImGui::TreeNodeEx(reinterpret_cast<void*>(entity), nodeFlags, "%s", entityName);

        if (ImGui::BeginPopupContextItem("Entity props"))
        {
            if (ImGui::MenuItem("Remove entity"))
                entitiesToDelete.insert(entity);
            ImGui::EndPopup();
        }

        if (ImGui::IsItemClicked())
            m_selectedEntity = entity;
        else if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
            ImGui::OpenPopup("Entity props");

        if (ImGui::IsItemHovered())
            m_hoveredEntity = entity;

    }

    for (auto entity : entitiesToDelete)
    {
        m_activeScene->deleteEntity(entity);
        if (m_selectedEntity == entity)
            m_selectedEntity = mx::NullEntity;
    }
}

void EditorLayer::showMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Close"))
                mx::Application::get().exit();

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void EditorLayer::showViewport()
{
    ImGui::Begin("Viewport");

    auto viewportPanelSize = ImGui::GetContentRegionAvail();

    m_viewPortSize = {viewportPanelSize.x, viewportPanelSize.y};

    ImTextureID texID = reinterpret_cast<ImTextureID>(m_framebuffer->getColorAttachement(0));
    auto& spec = m_framebuffer->getSpecification();
    ImGui::Image(texID, ImVec2(spec.Width, spec.Height));

    m_viewPortOnFocus = ImGui::IsWindowFocused();

    mx::Application::get().setImGuiEventsBlocking(!m_viewPortOnFocus && !ImGui::IsWindowHovered());

    ImGui::End();
}

void EditorLayer::showEntitiesWindow()
{
    ImGui::Begin("Hierarchy Panel");
    showActiveSceneEntities();

    if ((m_hoveredEntity == mx::NullEntity) && ImGui::BeginPopupContextWindow("Menu Popup"))
    {
        if (ImGui::MenuItem("Add Entity"))
            m_selectedEntity = m_activeScene->createEntity();
        ImGui::EndPopup();
    }

    ImGui::End();
}

void EditorLayer::showCurrentEntityComponents()
{
    ImGui::Begin("Properties");

    if (m_selectedEntity != mx::NullEntity)
    {
        if (m_openComponentsPopup && ImGui::BeginPopupContextWindow("Components Menu"))
        {
            if (ImGui::MenuItem("Transform2D component"))
            {
                if (!mx::EntityRegistry::hasComponent<mx::Transform2DComponent>(m_selectedEntity))
                    mx::EntityRegistry::addComponent<mx::Transform2DComponent>(m_selectedEntity);
                m_openComponentsPopup = false;
            }
            if (ImGui::MenuItem("Sprite renderer component"))
            {
                if (!mx::EntityRegistry::hasComponent<mx::SpriteRendererComponent>(m_selectedEntity))
                    mx::EntityRegistry::addComponent<mx::SpriteRendererComponent>(m_selectedEntity);
                m_openComponentsPopup = false;
            }

            ImGui::EndPopup();
        }
        if (ImGui::Button("Add component"))
        {
            ImGui::OpenPopup("Components Menu");
            m_openComponentsPopup = true;
        }

        if (ImGui::Button("Remove entity"))
        {
            m_activeScene->deleteEntity(m_selectedEntity);
            m_selectedEntity = mx::NullEntity;
        }

        if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
            m_openComponentsPopup = false;
        if (m_selectedEntity != mx::NullEntity)
            m_componentsDisplayer.displayComponents(m_selectedEntity);
    }
    ImGui::End();
}

