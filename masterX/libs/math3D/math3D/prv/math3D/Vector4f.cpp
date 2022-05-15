#include "Vector4f.hpp"
#include "Vector3f.hpp"
#include "Vector2f.hpp"

#include "math.hpp"

#ifdef USE_INSTRINSICS
    #include "simd/sse/Vector4f_sse.inl"
#endif


namespace math3D
{
    Vector4f Vector4f::Zero(0.0f);

    Vector4f::Vector4f(float _x, float _y, float _z, float _w)
        :x(_x), y(_y), z(_z), w(_w)
    {

    }

    Vector4f::Vector4f(float _xyzw):
        Vector4f(_xyzw, _xyzw, _xyzw, _xyzw)
    {

    }

    Vector4f::Vector4f(const Vector3f& _xyz, float _w)
        : Vector4f(_xyz.x, _xyz.y, _xyz.z, _w)
    {
    }
    
    Vector4f::Vector4f(const Vector2f& _xy, float _z, float _w)
        : Vector4f(_xy.x, _xy.y, _z, _w)
    {

    }

    Vector4f& Vector4f::operator*=(float l)
    {
        (*this) *= Vector4f(l);
        return *this;
    }

    Vector4f& Vector4f::operator/=(float l)
    {
        (*this) /= Vector4f(l);
        return *this;
    }

    Vector4f& Vector4f::normalize()
    {
        (*this) *= rsqrt(length2());
        return *this;
    }

    float Vector4f::length2() const
    {
        Vector4f copy(*this);
        copy *= copy;
        float sum = copy.x + copy.y + copy.z + copy.w;
        return sum;
    }


    // vector algebra

    Vector4f operator*(const Vector4f& u, float l)
    {
        return l * u;
    }

    float dotProduct(const Vector4f& v, const Vector4f& u)
    {
        Vector4f prod = v * u;

        float sum = prod.x + prod.y + prod.z + prod.w;

        return sum;
    }

    Vector4f normalize(const Vector4f& v)
    {
        Vector4f copy = v;

        return copy.normalize();
    }

    // comparison
    bool operator==(const Vector4f& v, const Vector4f& u)
    {
        return v.x == u.x && 
        v.y == u.y &&
        v.z == u.z &&
        v.w == u.w;
    }
    
    bool operator!=(const Vector4f& v, const Vector4f& u)
    {
        return !(v == u);
    }

    // io
    std::ostream& operator<<(std::ostream& stream, const Vector4f& v)
    {
        stream << '(' << v.x << ','
        << v.y << ','
        << v.z << ','
        << v.w << ')';

        return stream;
    }

    
}
