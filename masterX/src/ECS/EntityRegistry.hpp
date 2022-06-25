#pragma once

#include "EntityManager.hpp"
#include "ComponentManager.hpp"

namespace mx
{
    class EntityRegistry
    {
    public:

        static void init()
        {
            s_managers = Scope<Managers>::Create();
            s_managers->EntityManager = Scope<EntityManager>::Create();
            s_managers->ComponentManager = Scope<ComponentManager>::Create();
        }

        static void shutdown()
        {
            s_managers.reset();
        }

        static EntityID createEntity()
        {
            return s_managers->EntityManager->createEntity();
        }

        static void destroyEntity(EntityID entity)
        {
            s_managers->EntityManager->destroyEntity(entity);
        }

        template<typename T>
        static T& addComponent(EntityID entity)
        {
            T& cmp = s_managers->ComponentManager->addComponent<T>(entity);

            changeSignature<T>(entity, true);

            return cmp;
        }

        template<typename T>
        static void removeComponent(EntityID entity)
        {
            s_managers->ComponentManager->removeComponent<T>(entity);

            changeSignature<T>(entity, false);
        }

        template<typename T>
        static T& getComponent(EntityID entity)
        {
            return s_managers->ComponentManager->getComponent<T>(entity);
        }

        template<typename T>
        static bool hasComponent(EntityID entity)
        {
            return s_managers->ComponentManager->hasComponent<T>(entity);
        }

    private:

        template<typename T>
        static void changeSignature(EntityID entity, bool val)
        {
            Signature sig = s_managers->EntityManager->getSignature(entity);
            sig.set(s_managers->ComponentManager->getComponentID<T>(), val);
            s_managers->EntityManager->setSignature(entity, sig);
        }
    private:
        struct Managers
        {
            Scope<EntityManager> EntityManager;
            Scope<ComponentManager> ComponentManager;
        };

        static Scope<Managers> s_managers;
    };
}