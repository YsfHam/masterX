#pragma once

#include <immintrin.h>

#define mm_load_ps(p)\
(((long)(p)&15)==0?_mm_load_ps((p)):_mm_loadu_ps((p)))