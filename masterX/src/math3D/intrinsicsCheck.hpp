#pragma once

#ifdef USE_INTRINSICS
    #if !__SSE2__
        #error "Cannot compile with USE_INTRINSICS option : SSE2 is not enabled"
    #endif

    #include <immintrin.h>
#else
    #error "Please use intrinsics"
#endif