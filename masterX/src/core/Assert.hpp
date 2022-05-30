#pragma once


#ifdef MX_DEBUG
    #include "Log.hpp"
    #define MX_ASSERT_BREAK exit(-1)
    #define MX_IMP_ASSERT(cond, loggerName,fmt, ...) if (!(cond))\
    {MX_LOG_FATAL(loggerName, "Assertion Failed at {}:{}\n"#fmt, __FILE__, __LINE__); MX_ASSERT_BREAK;}
    #define MX_CORE_ASSERT(cond, fmt, ...)  MX_IMP_ASSERT(cond, "CORE", fmt, __VA_ARGS__);
    #define MX_ASSERT(cond, fmt, ...)  MX_IMP_ASSERT(cond, "APP", fmt, __VA_ARGS__);
#else
    #define MX_IMP_ASSERT(cond, loggerName, ...)
    #define MX_CORE_ASSERT(cond, ...)
    #define MX_ASSERT(cond, ...)
#endif