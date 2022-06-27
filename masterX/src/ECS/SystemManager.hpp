#pragma once

#include "settings.hpp"
#include "utils/types.hpp"

namespace mx
{
    class SystemManager;


    class System
    {
    protected:
        friend class SystemManager;
        std::unordered_set<EntityID> m_entities;
    };

    class SystemManager
    {
    public:
        template<typename T>
        Ref<T> registerSystem()
        {
            auto name = typeid(T).name();
            MX_CORE_ASSERT(m_systems.find(name) == m_systems.end(), "System already registered");
            auto system = Ref<T>::Create();
            m_systems[name] = system;

            return system;
        }

        template<typename T>
        void setSignature(Signature signature)
        {
            auto name = typeid(T).name();
            MX_CORE_ASSERT(m_systems.find(name) != m_systems.end(), "System is not registered");

            m_signatures[name] = signature;
        }

        void entityDestroyed(EntityID entity)
        {
           for (auto&[name, system] : m_systems)
           {
                system->m_entities.erase(entity);
           }
        }

        void entitySignatureChanged(EntityID entity, Signature signature)
        {
            for (auto&[name, system] : m_systems)
            {
                Signature& sig = m_signatures[name];

                if ((sig & signature) != sig)
                    system->m_entities.erase(entity);
                else
                    system->m_entities.insert(entity);
            }
        }

    private:
        std::unordered_map<const char*, Ref<System>> m_systems;
        std::unordered_map<const char*, Signature> m_signatures;
    };
}