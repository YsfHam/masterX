#include "mxpch.hpp"
#include "memory.hpp"

#include "core/Assert.hpp"

struct PointerData
{
    size_t Size;
    bool IsArray;
    PointerData(size_t size, bool isArray)
        : Size(size), IsArray(isArray)
    {}

    PointerData(size_t size)
        : PointerData(size, false)
    {}

    PointerData()
        :PointerData(0)
    {}
};

struct MemData
{
    size_t AllocatedMem = 0;
    size_t FreedMem = 0;

    uint32_t AllocationsNumber = 0;

    std::unordered_map<void*, PointerData> Pointers;
};

static MemData s_data;


namespace mx
{
    MemSize MemTracker::getAllocatedMemSize()
    {
        return s_data.AllocatedMem;
    }

    MemSize MemTracker::getFreedMemSize()
    {
        return s_data.FreedMem;
    }

    uint32_t MemTracker::getAllocationsNumber()
    {
        return s_data.AllocationsNumber;
    }


    void MemTracker::registerPointer(void *ptr, size_t size)
    {
        MX_CORE_TRACE("Register pointer address {}, size {}", ptr, size);
        s_data.AllocatedMem += size;
        s_data.Pointers[ptr] = PointerData(size);
        s_data.AllocationsNumber++;
    }

    void MemTracker::registerPointer(void *ptr, size_t unitSize, uint32_t count)
    {
        size_t size = unitSize * count;
        MX_CORE_TRACE("Register array pointer address {}, size {}", ptr, size);
        s_data.AllocatedMem += size;
        s_data.Pointers[ptr] = PointerData(size, true);
        s_data.AllocationsNumber++;
    }

    void MemTracker::unregisterPointer(void *ptr, bool& isArray)
    {
        MX_CORE_TRACE("Freeing memory {}", ptr);
        auto it = s_data.Pointers.find(ptr);
        MX_CORE_ASSERT(it != s_data.Pointers.end(), "This pointer is not allocated with this memory tracker");
        s_data.FreedMem += it->second.Size;
        isArray = it->second.IsArray;
        s_data.Pointers.erase(it);
        s_data.AllocationsNumber--;
    }
}