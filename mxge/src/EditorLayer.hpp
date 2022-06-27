#pragma once

#include <masterX.hpp>

class EditorLayer : public mx::Layer
{
public:
    EditorLayer();


    virtual void onAttach() override;
    virtual void onUpdate(mx::Time dt) override;
    virtual void onImguiRender() override;

private:
    void showActiveSceneEntities();

private:
    mx::Ref<mx::Framebuffer> m_framebuffer;
    math3D::Vector2f m_viewPortSize = math3D::Vector2f::Zero;

    mx::Camera2D m_editorCamera;

    mx::Ref<mx::Scene> m_activeScene;

    mx::EntityID m_selectedEntity = mx::NullEntity;
    mx::EntityID m_hoveredEntity = mx::NullEntity;

    mx::ComponentsDisplayer m_componentsDisplayer;
};