#include "mxpch.hpp"

#include "Camera2D.hpp"
#include "core/Log.hpp"

mx::Camera2D::Camera2D(float left, float right, float top, float bottom) 
    :
    m_position(0.0f),
    m_rotation(0.0f),
    m_projection(glm::ortho(left, right, bottom, top)),
    m_view(glm::mat4(1.0f)),
    m_transformChanged(true),
    m_pv(m_projection * m_view)
{
}

void mx::Camera2D::move(const glm::vec2& posOffset) 
{
    m_position += posOffset;
    m_transformChanged = true;
}

void mx::Camera2D::setPosition(const glm::vec2& position) 
{
    m_position = position;    
    m_transformChanged = true;

}

void mx::Camera2D::setProjection(float left, float right, float top, float bottom)
{
    m_projection = glm::ortho(left, right, bottom, top);
    m_pv = m_projection * m_view;
}

void mx::Camera2D::setRotation(const float angle) 
{
    m_rotation = angle;    
    m_transformChanged = true;
}

void mx::Camera2D::rotate(const float angle)
{
    m_rotation = m_rotation + angle;
    m_transformChanged = true;

}

glm::mat4 mx::Camera2D::getPV()
{
    if (m_transformChanged)
    {
        m_view = glm::mat4(1.0f);
        m_view = glm::transpose(glm::rotate(m_view, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f)));
        m_view = glm::translate(m_view, -1.f * glm::vec3(m_position, 0.0f));
        m_transformChanged = false;
        m_pv = m_projection * m_view;
    }

    return m_pv;
}
