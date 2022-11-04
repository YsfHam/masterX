#pragma once

#include "mxpch.hpp"
#include "core/Assert.hpp"

namespace mx
{

    using EntityID = std::uint32_t;
    constexpr EntityID MAX_ENTITIES = 5000; 
    constexpr EntityID NullEntity = 0;

    using ComponentID = std::uint8_t;
    constexpr ComponentID MAX_COMPONENTS = 16;  

    using Signature = std::bitset<MAX_COMPONENTS>;
}

#define CHECK_ENTITY(entity) MX_CORE_ASSERT((entity) <= MAX_ENTITIES && (entity) > 0, "Invalid Entity: {}", entity)
#define ENTITY_AS_INDEX(entity) ((entity) - 1)