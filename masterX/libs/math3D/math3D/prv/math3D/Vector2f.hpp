#pragma once

#include <iostream>

namespace math3D
{
    class Vector2f
    {
    public:
        Vector2f(float _x, float _y);
        Vector2f(float _xy);
        
        Vector2f& operator+=(const Vector2f& v);
        Vector2f& operator-=(const Vector2f& v);
        Vector2f& operator*=(const Vector2f& v);
        Vector2f& operator*=(float l);
        Vector2f& operator/=(const Vector2f& v);
        Vector2f& operator/=(float l);

        float length() const;
        float length2() const;
        Vector2f& normalize();

    public:
        float x, y;

        static Vector2f Zero;
    };

    // vector algebra
    Vector2f operator+(const Vector2f& v, const Vector2f& u);
    Vector2f operator-(const Vector2f& v, const Vector2f& u);
    Vector2f operator*(const Vector2f& v, const Vector2f& u);
    Vector2f operator*(float l, const Vector2f& v);
    Vector2f operator*(const Vector2f& u, float l);
    Vector2f operator/(const Vector2f& v, const Vector2f& u);
    Vector2f operator/(float l, const Vector2f& v);
    Vector2f operator/(const Vector2f& v, float l);
    
    float dotProduct(const Vector2f& v, const Vector2f& u);
    Vector2f normalize(const Vector2f& v);

    // comparison
    bool operator==(const Vector2f& v, const Vector2f& u);
    bool operator!=(const Vector2f& v, const Vector2f& u);

    Vector2f min(const Vector2f& v , const Vector2f& u);
    Vector2f max(const Vector2f& v , const Vector2f& u);

    // io
    std::ostream& operator<<(std::ostream& stream, const Vector2f& v);
}