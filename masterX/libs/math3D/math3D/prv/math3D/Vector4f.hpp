#pragma once

#include "instinctsCheck.hpp"

#include "Vector3f.hpp"
#include "Vector2f.hpp"

#include <iostream>

namespace math3D
{
    class Vector4f
    {
    public:
        Vector4f(float _x, float _y, float _z = 0.f, float _w = 1.0f);
        Vector4f(float _xyzw);
        Vector4f(const Vector3f& _xyz, float _w = 1.0f);
        Vector4f(const Vector2f& _xy, float _z = 0.0f, float _w = 1.0f);
        
        Vector4f& operator+=(const Vector4f& v);
        Vector4f& operator-=(const Vector4f& v);
        Vector4f& operator*=(const Vector4f& v);
        Vector4f& operator*=(float l);
        Vector4f& operator/=(const Vector4f& v);
        Vector4f& operator/=(float l);

        float length() const;
        float length2() const;
        Vector4f& normalize();

    public:
        float x, y, z, w;

        static Vector4f Zero;
    };

    // vector algebra
    Vector4f operator+(const Vector4f& v, const Vector4f& u);
    Vector4f operator-(const Vector4f& v, const Vector4f& u);
    Vector4f operator*(const Vector4f& v, const Vector4f& u);
    Vector4f operator*(float l, const Vector4f& v);
    Vector4f operator*(const Vector4f& u, float l);
    Vector4f operator/(const Vector4f& v, const Vector4f& u);
    Vector4f operator/(float l, const Vector4f& v);
    Vector4f operator/(const Vector4f& v, float l);
    
    float dotProduct(const Vector4f& v, const Vector4f& u);
    Vector4f normalize(const Vector4f& v);

    // comparison
    bool operator==(const Vector4f& v, const Vector4f& u);
    bool operator!=(const Vector4f& v, const Vector4f& u);

    Vector4f min(const Vector4f& v , const Vector4f& u);
    Vector4f max(const Vector4f& v , const Vector4f& u);

    // io
    std::ostream& operator<<(std::ostream& stream, const Vector4f& v);
}