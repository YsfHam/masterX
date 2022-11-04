#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mx
{
    class Camera2D
    {
    public:
        Camera2D(float left, float right, float top, float bottom);

        void move(const glm::vec2& posOffset);
        void setPosition(const glm::vec2& position);

        void setProjection(float left, float right, float top, float bottom);

        void setRotation(float angle);
        void rotate(float angle);

        glm::mat4 getPV();
        const glm::vec2& getPosition() const { return m_position; }
        const float getRotation() const { return m_rotation; }

    private:
        glm::vec2 m_position;
        float m_rotation;

        glm::mat4 m_projection;
        glm::mat4 m_view;
        glm::mat4 m_pv;
        bool m_transformChanged;
    };
}