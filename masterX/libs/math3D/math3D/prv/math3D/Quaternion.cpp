#include "Quaternion.hpp"

#include "math.hpp"

namespace math3D
{

    Quaternion::Quaternion(const Angle& angle, const Vector3f& v)
        : m_scalar(angle), m_imaginary(v)
    {
    }

    Quaternion::Quaternion(const Angle& angle, float i, float j, float k)
        : m_scalar(angle), m_imaginary(i, j, k)
    {
    }

    Quaternion::Quaternion(const Angle& angle)
        : m_scalar(angle), m_imaginary(Vector3f::Zero)
    {
    }

    Quaternion::Quaternion(float i, float j, float k)
        : m_scalar(0.0f), m_imaginary(i, j, k)
    {
    }

    Quaternion& Quaternion::operator+=(const Quaternion& q)
    {
        m_scalar = m_scalar.Degrees + q.m_scalar.Degrees;
        m_imaginary += q.m_imaginary;  

        return *this; 
    }

    Quaternion& Quaternion::operator-=(const Quaternion& q)
    {
        m_scalar = m_scalar.Degrees - q.m_scalar.Degrees;
        m_imaginary -= q.m_imaginary; 

        return *this;
    }

    Quaternion& Quaternion::operator*=(const Quaternion& q)
    {
        m_scalar = m_scalar.Degrees * q.m_scalar.Degrees - dotProduct(m_imaginary, q.m_imaginary);
        m_imaginary = m_scalar.Degrees * q.m_imaginary + 
                    q.m_scalar.Degrees * m_imaginary + crossProduct(m_imaginary, q.m_imaginary);

        return *this;
    }


    Quaternion operator+(const Quaternion& a, const Quaternion& b)
    {
        return Quaternion(a.m_scalar.Degrees + b.m_scalar.Degrees,
                             a.m_imaginary + b.m_imaginary);
    }

    Quaternion operator-(const Quaternion& a, const Quaternion& b)
    {
        return Quaternion(a.m_scalar.Degrees - b.m_scalar.Degrees,
                             a.m_imaginary - b.m_imaginary);
    }
    Quaternion operator*(const Quaternion& a, const Quaternion& b)
    {
        return Quaternion(
            a.m_scalar.Degrees * b.m_scalar.Degrees - dotProduct(a.m_imaginary, b.m_imaginary),
            a.m_scalar.Degrees * b.m_imaginary + b.m_scalar.Degrees * a.m_imaginary + crossProduct(a.m_imaginary, b.m_imaginary)
        );
    }

    Quaternion operator*(const Quaternion& a, float b)
    {
        return Quaternion(a.m_scalar.Degrees * b, a.m_imaginary * b);
    }

    Quaternion operator*(float a, const Quaternion& b)
    {
        return Quaternion(b.m_scalar.Degrees * a, b.m_imaginary * a);
    }

    Quaternion operator/(const Quaternion& a, const Quaternion& b)
    {
        return a * inverse(b);
    }

    Quaternion operator/(const Quaternion& a, float b)
    {
        return Quaternion(a.m_scalar.Degrees / b, a.m_imaginary / b);
    }

    Quaternion operator/(float a, const Quaternion& b)
    {
        return a * inverse(b);
    }

    Quaternion conjugate(const Quaternion& q)
    {
        return Quaternion(q.m_scalar, -1 * q.m_imaginary);
    }
        
    float norm(const Quaternion& q)
    {
        return std::sqrt(norm2(q));
    }

    float norm2(const Quaternion& q)
    {
        return (q * conjugate(q)).m_scalar.Degrees;
    }

    Quaternion normalize(const Quaternion& q)
    {
        return q * rsqrt(norm2(q));
    }

    Quaternion inverse(const Quaternion& q)
    {
        return conjugate(q) / norm2(q);
    }

    std::ostream& operator<<(std::ostream& stream, const Quaternion& q)
    {
        stream << q.m_scalar.Degrees;
        if (q.m_imaginary.x != 0)
        {
            if (q.m_imaginary.x > 0)
                stream << '+';
            stream << q.m_imaginary.x << 'i';

        }
        if (q.m_imaginary.y != 0)
        {
            if (q.m_imaginary.y > 0)
                stream << '+';
            stream << q.m_imaginary.y << 'j';

        }
        if (q.m_imaginary.z != 0)
        {
            if (q.m_imaginary.z > 0)
                stream << '+';
            stream << q.m_imaginary.z << 'k';

        }

        return stream;
    }
}