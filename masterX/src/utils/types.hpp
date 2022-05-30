#pragma once

#include "mxpch.hpp"

#include "memory.hpp"

namespace mx
{
    template<typename T>
    class Ref : public std::shared_ptr<T>
    {
    public:
        template<typename ...Args>
        static Ref<T> Create(Args&&...args)
        {
            //return std::make_shared<T>(std::forward<Args>(args)...);
            return std::shared_ptr<T>(MX_ALLOCATE(T, args...), [](T *ptr){
                MX_FREE(ptr);
            });
        }
        template <typename U>
        Ref(const std::shared_ptr<U>& ref)
        : std::shared_ptr<T>(ref)
        {}

        Ref()
        : std::shared_ptr<T>(nullptr)
        {}

        Ref(std::nullptr_t null)
        : std::shared_ptr<T>(null)
        {}
    };

    template<typename T>
    class Scope : public std::unique_ptr<T>
    {
    public:
        template<typename ...Args>
        static Scope<T> Create(Args&&...args)
        {
            return std::make_unique<T>(std::forward<Args>(args)...);
        }

        template <typename U>
        Scope(std::unique_ptr<U>&& ptr)
        : std::unique_ptr<T>(std::move(ptr))
        {}

        Scope()
        : std::unique_ptr<T>(nullptr)
        {
        }

        Scope(std::nullptr_t null)
        : std::unique_ptr<T>(null)
        {}
    };

    using RendererID = uint32_t;
}