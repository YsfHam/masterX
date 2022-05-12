#pragma once

#include "mxpch.hpp"

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
    };
}