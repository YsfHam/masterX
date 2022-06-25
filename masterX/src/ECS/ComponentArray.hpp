#pragma once

#include "settings.hpp"

namespace mx
{
    class ComponentArrayBase
    {
    public:
        virtual ~ComponentArrayBase() = default;
        virtual void entityDestroyed(EntityID entity) = 0;
    };

    template<typename T>
    class ComponentArray : public ComponentArrayBase
    {
    public:
        ComponentArray()
            : m_size(0)
        {
            std::memset(m_indexToEntity.data(), NullEntity, m_indexToEntity.size());
            std::memset(m_entityToIndex.data(), -1, m_entityToIndex.size());
        }
        T& add(EntityID entity, T component)
        {
            CHECK_ENTITY(entity);
            m_componentArray[m_size] = component;
            m_indexToEntity[m_size] = entity;
            m_entityToIndex[ENTITY_AS_INDEX(entity)] = m_size;
            m_size++;

            return m_componentArray[m_size - 1];
        }

        void remove(EntityID entity)
        {
            MX_CORE_ASSERT(exists(entity), "Removing non existing component");
            
            size_t cmpToRemoveIndex = m_entityToIndex[ENTITY_AS_INDEX(entity)];

            size_t lastElementIndex = m_size - 1;
            m_componentArray[cmpToRemoveIndex] = m_componentArray[lastElementIndex];

            EntityID lastCmpEntity = INDEX_AS_ENTITY(m_indexToEntity[lastElementIndex]);
            m_entityToIndex[ENTITY_AS_INDEX(lastCmpEntity)] = cmpToRemoveIndex;
            m_indexToEntity[cmpToRemoveIndex] = lastCmpEntity;

            m_entityToIndex[ENTITY_AS_INDEX(entity)] = -1;
            m_indexToEntity[lastElementIndex] = NullEntity;

            m_size--;
        }

        virtual void entityDestroyed(EntityID entity) override
        {
            if (exists(entity))
                remove(entity);
        }

        bool exists(EntityID entity)
        {
            CHECK_ENTITY(entity);
            return m_entityToIndex[ENTITY_AS_INDEX(entity)] != -1;
        }

        T& get(EntityID entity)
        {
            MX_CORE_ASSERT(exists(entity), "Component does not exist");
            return m_componentArray[m_entityToIndex[ENTITY_AS_INDEX(entity)]];
        }

        void print()
        {
            for (size_t i(0); i < m_size; i++)
                MX_CORE_INFO(m_componentArray[i]);
        }

    private:
        std::array<T, MAX_ENTITIES> m_componentArray;

        std::array<EntityID, MAX_ENTITIES> m_indexToEntity;
        std::array<size_t, MAX_ENTITIES> m_entityToIndex;
        size_t m_size;
    };
}