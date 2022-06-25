#pragma once

#include "ComponentArray.hpp"
#include "utils/types.hpp"

namespace mx
{
    class ComponentManager
    {
    public:
        ComponentManager()
            : m_nextID(0)
        {

        }
        template<typename T>
        T& addComponent(EntityID entity)
        {
            MX_CORE_ASSERT(!hasComponent<T>(entity), "entity {} already has {} component", entity, typeid(T).name());
            if (!isComponentRegistered<T>())
                registerComponent<T>();
            return getComponentArray<T>()->add(entity, T());
        }

        template<typename T>
        void removeComponent(EntityID entity)
        {
            MX_CORE_ASSERT(isComponentRegistered<T>(), "Component not registered");
            getComponentArray<T>()->remove(entity);
        }

        template<typename T>
        T& getComponent(EntityID entity)
        {
            MX_CORE_ASSERT(isComponentRegistered<T>(), "Component not registered");
            return getComponentArray<T>()->get(entity);
        }

        template<typename T>
        bool hasComponent(EntityID entity)
        {
            return isComponentRegistered<T>() &&
            getComponentArray<T>()->exists(entity);
        }

        void entityDestroyed(EntityID entity)
        {
            for (auto&[name, componentArray] : m_componentArrays)
                componentArray->entityDestroyed(entity);
        }

        template<typename T>
        ComponentID getComponentID()
        {
            auto name = typeid(T).name();
            auto it = m_componentIDs.find(name);
            MX_CORE_ASSERT(it != m_componentIDs.end(), "Component not registered");
            return it->second;
        }

    private:
        template<typename T>
        Ref<ComponentArray<T>> getComponentArray()
        {
            auto name = typeid(T).name();

            return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[name]);
        }

        template<typename T>
        bool isComponentRegistered()
        {
            auto name = typeid(T).name();
            return m_componentArrays.find(name) != m_componentArrays.end();
        }

        template<typename T>
        void registerComponent()
        {
            MX_CORE_ASSERT(m_nextID < MAX_COMPONENTS, "Too many components");

            auto name = typeid(T).name();
            m_componentArrays[name] = Ref<ComponentArray<T>>::Create();
            m_componentIDs[name] = m_nextID++;
        }

    private:
        std::unordered_map<const char*, Ref<ComponentArrayBase>> m_componentArrays;
        std::unordered_map<const char*, ComponentID> m_componentIDs;

        ComponentID m_nextID;
    };
}