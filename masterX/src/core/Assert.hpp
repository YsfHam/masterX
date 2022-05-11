#pragma once


#ifdef MX_DEBUG
    #include "Log.hpp"
    #define MX_ASSERT_BREAK exit(-1)
    #define MX_IMP_ASSERT(cond, loggerName, ...) if (!(cond)){MX_LOG_FATAL(loggerName, __VA_ARGS__); MX_ASSERT_BREAK;}
    #define MX_CORE_ASSERT(cond, ...)  MX_IMP_ASSERT(cond, "CORE", __VA_ARGS__);
    #define MX_ASSERT(cond, ...)  MX_IMP_ASSERT(cond, "APP", __VA_ARGS__);
#else
    #define MX_IMP_ASSERT(cond, loggerName, ...)
    #define MX_CORE_ASSERT(cond, ...)
    #define MX_ASSERT(cond, ...)
#endif