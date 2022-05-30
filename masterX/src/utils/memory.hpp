#pragma once

#include <cstdlib>
#include "mxpch.hpp"


namespace mx
{
    class MemTracker
    {
    public:
        static size_t getAllocatedMemSize();
        static size_t getFreedMemSize();
        static uint32_t getAllocationsNumber();
        static void free(void* ptr);

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