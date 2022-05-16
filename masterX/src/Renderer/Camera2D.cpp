#include "Camera2D.hpp"


mx::Camera2D::Camera2D(float left, float right, float top, float bottom) 
    :
    m_position(math3D::Vector2f::Zero),
    m_rotation(0.0f),
    m_projection(math3D::orthographic2D(left, right, top, bottom)),
    m_view(math3D::Matrix3f::Identity),
    m_transformChanged(true)
{
    
}

void mx::Camera2D::move(const math3D::Vector2f& posOffset) 
{
    m_position += posOffset;
    m_transformChanged = true;
}

void mx::Camera2D::setPosition(const math3D::Vector2f& position) 
{
    m_position = position;    
    m_transformChanged = true;

}

void mx::Camera2D::setRotation(const math3D::Angle& angle) 
{
    m_rotation = angle;    
    m_transformChanged = true;

}

void mx::Camera2D::rotate(const math3D::Angle& angle)
{
    m_rotation = m_rotation.Degrees + angle.Degrees;
    m_transformChanged = true;

}

math3D::Matrix3f mx::Camera2D::getPV()
{
    if (m_transformChanged)
    {
        m_view = math3D::Matrix3f::Identity;
        m_view = math3D::rotate2D(m_view, m_rotation).transpose();
        m_view = math3D::translate2D(m_view, -1 * m_position);
        m_transformChanged = false;
    }

    return m_projection * m_view;
}
