#pragma once

#include "mxpch.hpp"

#include "core/Assert.hpp"

namespace mx
{
    template<typename T>
    class Ref : public std::shared_ptr<T>
    {
    public:
        template<typename ...Args>
        static Ref<T> Create(Args&&...args)
        {
            return std::make_shared<T>(std::forward<Args>(args)...);
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

        T* operator->()
        {
            MX_CORE_ASSERT(this->get() != nullptr, "Null pointer access");

            return std::shared_ptr<T>::operator->();
        }
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

        T* operator->()
        {
            MX_CORE_ASSERT(this->get() != nullptr, "Null pointer access");

            return std::unique_ptr<T>::operator->();
        }
    };

    using RendererID = uint32_t;
}