#pragma once

#define SWIZZLE_VEC2(cmp1, cmp2)\
struct\
{\
float cmp1, cmp2;\
operator Vector2f()\
{\
return Vector2f(cmp1, cmp2);\
}\
Vector2f toVector()\
{\
return (Vector2f)(*this);\
}\
}

#define SWIZZLE_VEC3(cmp1, cmp2, cmp3)\
struct\
{\
float cmp1, cmp2, cmp3;\
operator Vector3f()\
{\
return Vector3f(cmp1, cmp2, cmp3);\
}\
Vector3f toVector()\
{\
return (Vector3f)(*this);\
}\
}

#define SWIZZLE_VEC4(cmp1, cmp2, cmp3, cmp4)\
struct\
{\
float cmp1, cmp2, cmp3, cmp4;\
operator Vector4f()\
{\
return Vector4f(cmp1, cmp2, cmp3, cmp4);\
}\
Vector4f toVector()\
{\
return (Vector4f)(*this);\
}\
}