#pragma once

#include "intrinsicsCheck.hpp"
#include "Vector2f.hpp"
#include "swizzle.hpp"

#include <iostream>

namespace math3D
{
    class Vector3f
    {
    public:
        Vector3f(float _x, float _y, float _z = 0.f);
        Vector3f(float _xyz);
        Vector3f(const Vector2f& v, float _z = 0.f);
        
        Vector3f& operator+=(const Vector3f& v);
        Vector3f& operator-=(const Vector3f& v);
        Vector3f& operator*=(const Vector3f& v);
        Vector3f& operator*=(float l);
        Vector3f& operator/=(const Vector3f& v);
        Vector3f& operator/=(float l);

        float length() const;
        float length2() const;
        Vector3f& normalize();

        std::ostream& print(std::ostream& stream) const;


    public:
        union
        {
            struct
            {
                float x, y, z;
            };
            SWIZZLE_VEC2(x, y) xy;
        };

        static Vector3f Zero;
    };

    // vector algebra
    Vector3f operator+(const Vector3f& v, const Vector3f& u);
    Vector3f operator-(const Vector3f& v, const Vector3f& u);
    Vector3f operator*(const Vector3f& v, const Vector3f& u);
    Vector3f operator*(float l, const Vector3f& v);
    Vector3f operator*(const Vector3f& u, float l);
    Vector3f operator/(const Vector3f& v, const Vector3f& u);
    Vector3f operator/(float l, const Vector3f& v);
    Vector3f operator/(const Vector3f& v, float l);
    
    float dotProduct(const Vector3f& v, const Vector3f& u);
    Vector3f crossProduct(const Vector3f& v, const Vector3f& u);
    Vector3f normalize(const Vector3f& v);

    // comparison
    bool operator==(const Vector3f& v, const Vector3f& u);
    bool operator!=(const Vector3f& v, const Vector3f& u);

    Vector3f min(const Vector3f& v , const Vector3f& u);
    Vector3f max(const Vector3f& v , const Vector3f& u);
}