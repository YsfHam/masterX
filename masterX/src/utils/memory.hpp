#pragma once

#include <cstdlib>
#include "mxpch.hpp"


namespace mx
{

    class MemSize
    {
    public:
        MemSize(size_t memSize)
            : m_memSize(memSize)
        {}

        float kb() const { return m_memSize / 1024.0f; }
        float mb() const { return kb() / 1024.0f; }
        float gb() const { return mb() / 1024.0f; }

        operator size_t() { return m_memSize; }

    private:
        size_t m_memSize;
    };

    class MemTracker
    {
    public:
        static void init();
        static void shutdown();

        static MemSize getAllocatedMemSize();
        static MemSize getFreedMemSize();
        static uint32_t getAllocationsNumber();

        template<typename T, typename ...Args>
        static T* allocate(Args&& ...args)
        {
            T *ptr = new T(std::forward<Args>(args)...);

            registerPointer(ptr, sizeof(T));
            return ptr;
        }

        template<typename T>
        static T* allocateArray(uint32_t count)
        {
            T *ptr = new T[count];

            registerPointer(ptr, sizeof(T), count);
            return ptr;
        }

        template<typename T>
        static void free(T *ptr)
        {
            bool isArray;
            unregisterPointer(ptr, isArray);
            if (isArray)
                delete[] ptr;
            else
                delete ptr;
        }

    private:
        static void registerPointer(void *ptr, size_t size);
        static void registerPointer(void *ptr, size_t unitSize, uint32_t count);
        static void unregisterPointer(void *ptr, bool& isArray);
    };
}

#define MX_ALLOCATE(type, ...) MemTracker::allocate<type>(__VA_ARGS__)
#define MX_ALLOCATE_ARRAY(type, count) MemTracker::allocateArray<type>(count)
#define MX_FREE(ptr) MemTracker::free(ptr)