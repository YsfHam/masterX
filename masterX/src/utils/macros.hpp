#pragma once

#include "mxpch.hpp"

#define MX_BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)