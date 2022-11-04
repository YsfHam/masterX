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
        void deleteEntity(EntityID entity);

        void renderScene(Camera2D& camera);
        
        std::unordered_set<EntityID>::iterator begin() { return m_entities.begin(); }
        std::unordered_set<EntityID>::iterator end() { return m_entities.end(); }

    private:
        std::unordered_set<EntityID> m_entities;

        Ref<RendererSystem> m_rendererSystem;
    };
}