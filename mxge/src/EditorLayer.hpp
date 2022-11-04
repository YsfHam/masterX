#pragma once

#include <masterX.hpp>

#include <glm/glm.hpp>

class EditorLayer : public mx::Layer
{
public:
    EditorLayer();


    virtual void onAttach() override;
    virtual void onUpdate(mx::Time dt) override;
    virtual void onImguiRender() override;

private:
    void showActiveSceneEntities();
    void showMainMenuBar();
    void showViewport();
    void showEntitiesWindow();
    void showCurrentEntityComponents();

private:
    mx::Ref<mx::Framebuffer> m_framebuffer;

    glm::vec2 m_viewPortSize = glm::vec2(0.0f);

    mx::Camera2D m_editorCamera;
    glm::vec2 m_mouseDragDelta = glm::vec2(0.0f);
    glm::vec2 m_mouseInitialPosition = glm::vec2(0.0f);


    mx::Ref<mx::Scene> m_activeScene;

    mx::EntityID m_selectedEntity = mx::NullEntity;
    mx::EntityID m_hoveredEntity = mx::NullEntity;

    mx::ComponentsDisplayer m_componentsDisplayer;

    bool m_viewPortOnFocus = false;
    bool m_openComponentsPopup = false;

};