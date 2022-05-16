#pragma once

#include "math3D/math3D.hpp"

namespace mx
{
    class Camera2D
    {
    public:
        Camera2D(float left, float right, float top, float bottom);

        void move(const math3D::Vector2f& posOffset);
        void setPosition(const math3D::Vector2f& position);

        void setRotation(const math3D::Angle& angle);
        void rotate(const math3D::Angle& angle);

        math3D::Matrix3f getPV();

        const math3D::Vector2f& getPosition() const { return m_position; }
        const math3D::Angle& getRotation() const { return m_rotation; }

    private:
        math3D::Vector2f m_position;
        math3D::Angle m_rotation;

        math3D::Matrix3f m_projection;

        math3D::Matrix3f m_view;
        bool m_transformChanged;
    };
}