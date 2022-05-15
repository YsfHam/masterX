#include "Vector3f.hpp"

#include "math.hpp"


#ifdef USE_INSTRINSICS
    #include "simd/sse/Vector3f_sse.inl"
#endif


namespace math3D
{

    Vector3f Vector3f::Zero(0.0f);

    Vector3f::Vector3f(float _x, float _y, float _z)
        :x(_x), y(_y), z(_z)
    {

    }

    Vector3f::Vector3f(float _xyz):
        Vector3f(_xyz, _xyz, _xyz)
    {

    }

    Vector3f& Vector3f::operator*=(float l)
    {
        (*this) *= Vector3f(l);
        return *this;
    }

    Vector3f& Vector3f::operator/=(float l)
    {
        (*this) /= Vector3f(l);
        return *this;
    }

    Vector3f& Vector3f::normalize()
    {
        (*this) *= rsqrt(length2());
        return *this;
    }

    float Vector3f::length2() const
    {
        Vector3f copy(*this);
        copy *= copy;
        float sum = copy.x + copy.y + copy.z;
        return sum;
    }


    // vector algebra

    Vector3f operator*(const Vector3f& u, float l)
    {
        return l * u;
    }

    float dotProduct(const Vector3f& v, const Vector3f& u)
    {
        Vector3f prod = v * u;

        float sum = prod.x + prod.y + prod.z;

        return sum;
    }

    Vector3f crossProduct(const Vector3f& v, const Vector3f& u)
    {
        Vector3f result = Vector3f::Zero;

        result.x = v.y * u.z - v.z * u.y;
        result.y = v.z * u.x - v.x * u.z;
        result.z = v.x * u.y - v.y * u.x;

        return result;
    }

    Vector3f normalize(const Vector3f& v)
    {
        Vector3f copy = v;

        return copy.normalize();
    }

    // comparison
    bool operator==(const Vector3f& v, const Vector3f& u)
    {
        return v.x == u.x && 
        v.y == u.y &&
        v.z == u.z;
    }
    
    bool operator!=(const Vector3f& v, const Vector3f& u)
    {
        return !(v == u);
    }

    // io
    std::ostream& operator<<(std::ostream& stream, const Vector3f& v)
    {
        stream << '(' << v.x << ','
        << v.y << ','
        << v.z << ')';

        return stream;
    }

    
}
