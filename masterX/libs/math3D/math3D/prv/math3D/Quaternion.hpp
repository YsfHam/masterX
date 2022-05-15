#pragma once

#include "Vector3f.hpp"

#include "math.hpp"

namespace math3D
{
    class Quaternion
    {
    public:
        Quaternion(const Angle& angle, const Vector3f& v);
        Quaternion(const Angle& angle, float i, float j, float k);
        Quaternion(const Angle& angle);
        Quaternion(float i, float j, float k);

        inline float getReal() {return m_scalar.Degrees; }
        inline Vector3f getImaginary() { return m_imaginary; }

        Quaternion& operator+=(const Quaternion& q);
        Quaternion& operator-=(const Quaternion& q);
        Quaternion& operator*=(const Quaternion& q);

        // operators
        friend Quaternion operator+(const Quaternion& a, const Quaternion& b);
        friend Quaternion operator-(const Quaternion& a, const Quaternion& b);
        friend Quaternion operator*(const Quaternion& a, const Quaternion& b);
        friend Quaternion operator*(const Quaternion& a, float b);
        friend Quaternion operator*(float a, const Quaternion& b);
        friend Quaternion operator/(const Quaternion& a, const Quaternion& b);
        friend Quaternion operator/(const Quaternion& a, float b);
        friend Quaternion operator/(float a, const Quaternion& b);
        
        friend Quaternion conjugate(const Quaternion& q);
        friend float norm(const Quaternion& q);
        friend float norm2(const Quaternion& q);
        friend Quaternion normalize(const Quaternion& q);
        friend Quaternion inverse(const Quaternion& q);

        friend std::ostream& operator<<(std::ostream& stream, const Quaternion& q);


    private:
        Angle m_scalar;

        Vector3f m_imaginary;
    };
}