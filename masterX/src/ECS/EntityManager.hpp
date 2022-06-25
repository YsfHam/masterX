#pragma once

#include "settings.hpp"

namespace mx
{
    class EntityManager
    {
    public:

        EntityManager()
            : m_livingEntities(0)
        {
            for (EntityID entity = 1; entity <= MAX_ENTITIES; entity++)
                m_entities.push(entity);
        }

        EntityID createEntity()
        {
            MX_CORE_ASSERT(m_livingEntities < MAX_ENTITIES, "Too many entities");
            EntityID newEntity = m_entities.front();
            m_entities.pop();
            m_livingEntities++;
            return newEntity;
        }

        void destroyEntity(EntityID entity)
        {
            CHECK_ENTITY(entity);

            m_entities.push(entity);
            m_livingEntities--;
        }

        void setSignature(EntityID entity, Signature signature)
        {
            CHECK_ENTITY(entity);
            m_signatures[entity - 1] = signature;
        }

        Signature getSignature(EntityID entity)
        {
            CHECK_ENTITY(entity);
            return m_signatures[entity - 1];
        }

    private:
        std::queue<EntityID> m_entities;

        std::array<Signature, MAX_ENTITIES> m_signatures;

        uint32_t m_livingEntities;
    };
}