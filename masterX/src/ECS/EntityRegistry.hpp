#pragma once

#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"

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
            s_managers->SystemManager = Scope<SystemManager>::Create();
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
            s_managers->ComponentManager->entityDestroyed(entity);
            s_managers->SystemManager->entityDestroyed(entity);
        }

        template<typename T, typename ...Args>
        static T& addComponent(EntityID entity, Args&&...args)
        {
            T& cmp = s_managers->ComponentManager->addComponent<T>(entity, args...);

            changeSignature<T>(entity, true);

            return cmp;
        }

        template<typename T, typename ...Args>
        static T& addComponentIfNotExists(EntityID entity, Args&& ...args)
        {
            if (!hasComponent<T>(entity))
                addComponent<T>(entity, args...);
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

        template<typename T>
        static ComponentID getComponentID()
        {
            return s_managers->ComponentManager->getComponentID<T>();
        }

        template<typename T, typename ...SigCmps>
        static Ref<T> registerSystem()
        {
            MX_CORE_ASSERT(sizeof...(SigCmps) > 0, "Ivalid system signature");
            auto system = s_managers->SystemManager->registerSystem<T>();

            Signature sig;
            if constexpr (sizeof...(SigCmps) > 0)
                generateSignature<SigCmps...>(sig);
            s_managers->SystemManager->setSignature<T>(sig);

            for (EntityID entity = 1; entity < MAX_ENTITIES; entity++) 
            {
                s_managers->SystemManager->entitySignatureChanged(entity, s_managers->EntityManager->getSignature(entity));
            }

            return system;
        }

    private:

        template<typename T>
        static void changeSignature(EntityID entity, bool val)
        {
            Signature sig = s_managers->EntityManager->getSignature(entity);
            sig.set(s_managers->ComponentManager->getComponentID<T>(), val);
            s_managers->EntityManager->setSignature(entity, sig);
            s_managers->SystemManager->entitySignatureChanged(entity, sig);
        }

        template<typename T, typename ...Rest>
        static void generateSignature(Signature& sig)
        {
            if (!s_managers->ComponentManager->isComponentRegistered<T>())
                s_managers->ComponentManager->registerComponent<T>();
            sig.set(s_managers->ComponentManager->getComponentID<T>());

            if constexpr (sizeof ...(Rest) > 0)
                generateSignature<Rest...>(sig);
        }

    private:
        struct Managers
        {
            Scope<EntityManager> EntityManager;
            Scope<ComponentManager> ComponentManager;
            Scope<SystemManager> SystemManager;
        };

        static Scope<Managers> s_managers;
    };
}