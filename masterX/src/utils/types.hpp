#pragma once

#include "mxpch.hpp"

namespace utils
{
    template<typename T>
    using Ref = std::shared_ptr<T>;
}