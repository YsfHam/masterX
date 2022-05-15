#include "math3D/Vector3f.hpp"
#include <cstring>

namespace math3D
{

    static __m128 loadVec3(const Vector3f& vec)
    {
        float arr[4] =  {0.0f};
        float *vecFloatPtr = (float*)&vec;
        std::memcpy(arr, vecFloatPtr, 3 * sizeof(float));

        return _mm_load_ps(arr);
    }

    Vector3f& Vector3f::operator+=(const Vector3f& v)
    {
        __m128 _self = loadVec3(*this);
        __m128 _v = loadVec3(v);

        _self = _mm_add_ps(_self, _v);
        x = _self[0];
        y = _self[1];
        z = _self[2];

        return *this;
    }

    Vector3f& Vector3f::operator-=(const Vector3f& v)
    {
        __m128 _self = loadVec3(*this);
        __m128 _v = loadVec3(v);

        _self = _mm_sub_ps(_self, _v);
        x = _self[0];
        y = _self[1];
        z = _self[2];

        return *this;
    }

    Vector3f& Vector3f::operator*=(const Vector3f& v)
    {
        __m128 _self = loadVec3(*this);
        __m128 _v = loadVec3(v);
        _self = _mm_mul_ps(_self, _v);

        x = _self[0];
        y = _self[1];
        z = _self[2];

        return *this;
    }

    Vector3f& Vector3f::operator/=(const Vector3f& v)
    {
        __m128 _self = loadVec3(*this);
        __m128 _v = loadVec3(v);
        _self = _mm_div_ps(_self, _v);

        x = _self[0];
        y = _self[1];
        z = _self[2];
        return *this;
    }

    float Vector3f::length() const
    {
        Vector3f copy(*this);
        copy *= copy;
        float sum = copy.x + copy.y + copy.z;
        __m128 _squareRoot = _mm_load_ps(&sum);
        _squareRoot = _mm_sqrt_ps(_squareRoot);
        return _squareRoot[0];
    }

    Vector3f operator+(const Vector3f& v, const Vector3f& u)
    {
        Vector3f result = Vector3f::Zero;

        __m128 _v = loadVec3(v);
        __m128 _u = loadVec3(u);

        __m128 _result = _mm_add_ps(_v, _u);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];

        return result;
    }

    Vector3f operator-(const Vector3f& v, const Vector3f& u)
    {
        Vector3f result = Vector3f::Zero;

        __m128 _v = loadVec3(v);
        __m128 _u = loadVec3(u);

        __m128 _result = _mm_sub_ps(_v, _u);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];

        return result;
    }

    Vector3f operator*(const Vector3f& v, const Vector3f& u)
    {
        Vector3f result = Vector3f::Zero;

        __m128 _v = loadVec3(v);
        __m128 _u = loadVec3(u);

        __m128 _result = _mm_mul_ps(_v, _u);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];

        return result;
    }

    Vector3f operator*(float l, const Vector3f& v)
    {
        Vector3f result = Vector3f::Zero;

        float lVec[] = {l, l, l, l};

        __m128 _v = loadVec3(v);
        __m128 _l = _mm_load_ps(lVec);

        __m128 _result = _mm_mul_ps(_v, _l);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];

        return result;
    }

    Vector3f operator/(const Vector3f& v, const Vector3f& u)
    {
        Vector3f result = Vector3f::Zero;

         __m128 _v = loadVec3(v);
        __m128 _u = loadVec3(u);

        __m128 _result = _mm_div_ps(_v, _u);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];

        return result;
    }

    Vector3f operator/(float l, const Vector3f& v)
    {
       Vector3f result = Vector3f::Zero;

        float lVec[] = {l, l, l, l};

        __m128 _v = loadVec3(v);
        __m128 _l = _mm_load_ps(lVec);

        __m128 _result = _mm_div_ps(_l, _v);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];

        return result;
    }

    Vector3f operator/(const Vector3f& v, float l)
    {
        Vector3f result = Vector3f::Zero;

        float lVec[] = {l, l, l, l};

        __m128 _v = loadVec3(v);
        __m128 _l = _mm_load_ps(lVec);

        __m128 _result = _mm_div_ps(_v, _l);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];

        return result;
    }

    Vector3f min(const Vector3f& v , const Vector3f& u)
    {
        __m128 _v = loadVec3(v);
        __m128 _u = loadVec3(u);

        __m128 _max = _mm_min_ps(_v, _u);

        return Vector3f(_max[0], _max[1], _max[2]);
    }

    Vector3f max(const Vector3f& v , const Vector3f& u)
    {
        __m128 _v = loadVec3(v);
        __m128 _u = loadVec3(u);

        __m128 _max = _mm_max_ps(_v, _u);

        return Vector3f(_max[0], _max[1], _max[2]);
    }
}
