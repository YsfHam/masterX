#include "math3D/Vector4f.hpp"

namespace math3D
{
    Vector4f& Vector4f::operator+=(const Vector4f& v)
    {
        __m128 _self = _mm_load_ps((float*)this);
        __m128 _v = _mm_load_ps((float*)&v);

        _self = _mm_add_ps(_self, _v);
        x = _self[0];
        y = _self[1];
        z = _self[2];
        w = _self[3];

        return *this;
    }

    Vector4f& Vector4f::operator-=(const Vector4f& v)
    {
        __m128 _self = _mm_load_ps((float*)this);
        __m128 _v = _mm_load_ps((float*)&v);

        _self = _mm_sub_ps(_self, _v);
        x = _self[0];
        y = _self[1];
        z = _self[2];
        w = _self[3];

        return *this;
    }

    Vector4f& Vector4f::operator*=(const Vector4f& v)
    {
        __m128 _self = _mm_load_ps((float*)this);
        __m128 _v = _mm_load_ps((float*)&v);
        _self = _mm_mul_ps(_self, _v);

        x = _self[0];
        y = _self[1];
        z = _self[2];
        w = _self[3];

        return *this;
    }

    Vector4f& Vector4f::operator/=(const Vector4f& v)
    {
        __m128 _self = _mm_load_ps((float*)this);
        __m128 _v = _mm_load_ps((float*)&v);
        _self = _mm_div_ps(_self, _v);

        x = _self[0];
        y = _self[1];
        z = _self[2];
        w = _self[3];
        return *this;
    }

    float Vector4f::length() const
    {
        Vector4f copy(*this);
        copy *= copy;
        float sum = copy.x + copy.y + copy.z + copy.w;
        __m128 _squareRoot = _mm_load_ps(&sum);
        _squareRoot = _mm_sqrt_ps(_squareRoot);
        return _squareRoot[0];
    }
    
    Vector4f operator+(const Vector4f& v, const Vector4f& u)
    {
        Vector4f result = Vector4f::Zero;

        __m128 _v = _mm_load_ps((float*)&v);
        __m128 _u = _mm_load_ps((float*)&u);

        __m128 _result = _mm_add_ps(_v, _u);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];
        result.w = _result[3];

        return result;
    }

    Vector4f operator-(const Vector4f& v, const Vector4f& u)
    {
        Vector4f result = Vector4f::Zero;

        __m128 _v = _mm_load_ps((float*)&v);
        __m128 _u = _mm_load_ps((float*)&u);

        __m128 _result = _mm_sub_ps(_v, _u);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];
        result.w = _result[3];

        return result;
    }

    Vector4f operator*(const Vector4f& v, const Vector4f& u)
    {
        Vector4f result = Vector4f::Zero;

        __m128 _v = _mm_load_ps((float*)&v);
        __m128 _u = _mm_load_ps((float*)&u);

        __m128 _result = _mm_mul_ps(_v, _u);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];
        result.w = _result[3];

        return result;
    }

    Vector4f operator*(float l, const Vector4f& v)
    {
        Vector4f result = Vector4f::Zero;

        float lVec[] = {l, l, l, l};

        __m128 _v = _mm_load_ps((float*)&v);
        __m128 _l = _mm_load_ps(lVec);

        __m128 _result = _mm_mul_ps(_v, _l);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];
        result.w = _result[3];

        return result;
    }

    Vector4f operator/(const Vector4f& v, const Vector4f& u)
    {
        Vector4f result = Vector4f::Zero;

        __m128 _v = _mm_load_ps((float*)&v);
        __m128 _u = _mm_load_ps((float*)&u);

        __m128 _result = _mm_div_ps(_v, _u);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];
        result.w = _result[3];

        return result;
    }

    Vector4f operator/(float l, const Vector4f& v)
    {
       Vector4f result = Vector4f::Zero;

        float lVec[] = {l, l, l, l};

        __m128 _v = _mm_load_ps((float*)&v);
        __m128 _l = _mm_load_ps(lVec);

        __m128 _result = _mm_div_ps(_l, _v);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];
        result.w = _result[3];

        return result;
    }

    Vector4f operator/(const Vector4f& v, float l)
    {
        Vector4f result = Vector4f::Zero;

        float lVec[] = {l, l, l, l};

        __m128 _v = _mm_load_ps((float*)&v);
        __m128 _l = _mm_load_ps(lVec);

        __m128 _result = _mm_div_ps(_v, _l);

        result.x = _result[0];
        result.y = _result[1];
        result.z = _result[2];
        result.w = _result[3];

        return result;
    }

    Vector4f min(const Vector4f& v , const Vector4f& u)
    {
        __m128 _v = _mm_load_ps((float*)&v);
        __m128 _u = _mm_load_ps((float*)&u);

        __m128 _max = _mm_min_ps(_v, _u);

        return Vector4f(_max[0], _max[1], _max[2], _max[3]);
    }

    Vector4f max(const Vector4f& v , const Vector4f& u)
    {
        __m128 _v = _mm_load_ps((float*)&v);
        __m128 _u = _mm_load_ps((float*)&u);

        __m128 _max = _mm_max_ps(_v, _u);

        return Vector4f(_max[0], _max[1], _max[2], _max[3]);
    }
}
