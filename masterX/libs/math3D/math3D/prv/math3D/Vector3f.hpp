#pragma once

#include "instinctsCheck.hpp"

#include <iostream>

namespace math3D
{
    class Vector3f
    {
    public:
        Vector3f(float _x, float _y, float _z = 0.f);
        Vector3f(float _xyz);
        
        Vector3f& operator+=(const Vector3f& v);
        Vector3f& operator-=(const Vector3f& v);
        Vector3f& operator*=(const Vector3f& v);
        Vector3f& operator*=(float l);
        Vector3f& operator/=(const Vector3f& v);
        Vector3f& operator/=(float l);

        float length() const;
        float length2() const;
        Vector3f& normalize();

    public:
        float x, y, z;

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

    // io
    std::ostream& operator<<(std::ostream& stream, const Vector3f& v);
}