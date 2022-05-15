#pragma once

#ifdef USE_INSTRINSICS
    #if !__SSE2__
        #error "Cannot compile with USE_INSTINCTS option : SSE2 is not enabled"
    #endif

    #include <emmintrin.h>
#else
    #error "Please use intrinsics"
#endif