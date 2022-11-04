#include "mxpch.hpp"
#include "Scene.hpp"

#include "components.hpp"

namespace mx
{
    Scene::Scene() 
    {
        m_rendererSystem = EntityRegistry::registerSystem<RendererSystem, Transform2DComponent, SpriteRendererComponent>();
    }

    EntityID Scene::createEntity(const std::string& name) 
    {
        EntityID entity = EntityRegistry::createEntity();
        auto& tagComponent = EntityRegistry::addComponent<TagComponent>(entity);
        tagComponent.Tag = name.empty() ? "new Entity " + std::to_string(entity) : name;

        m_entities.insert(entity);

        return entity;
    }

    void Scene::deleteEntity(EntityID entity)
    {
        EntityRegistry::destroyEntity(entity);

        m_entities.erase(entity);
    }

    void Scene::renderScene(Camera2D& camera) 
    {
        m_rendererSystem->render(camera);
    }
}

