#pragma once

#include "ecs.hpp"
#include "systems.hpp"

namespace mx
{
    class Scene
    {
    public:
        Scene();

        EntityID createEntity(const std::string& name = "");

        void renderScene(Camera2D& camera);
        
        std::vector<EntityID>::iterator begin() { return m_entities.begin(); }
        std::vector<EntityID>::iterator end() { return m_entities.end(); }

    private:
        std::vector<EntityID> m_entities;

        Ref<RendererSystem> m_rendererSystem;
    };
}