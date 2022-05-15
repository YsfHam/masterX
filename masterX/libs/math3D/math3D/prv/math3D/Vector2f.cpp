#include "Vector2f.hpp"

#include <cmath>

#include "math.hpp"



namespace math3D
{
    Vector2f Vector2f::Zero(0.0f);

    Vector2f::Vector2f(float _x, float _y)
        :x(_x), y(_y)
    {

    }

    Vector2f::Vector2f(float _xy):
        Vector2f(_xy, _xy)
    {}

    Vector2f& Vector2f::operator*=(float l)
    {
        (*this) *= Vector2f(l);
        return *this;
    }

    Vector2f& Vector2f::operator/=(float l)
    {
        (*this) /= Vector2f(l);
        return *this;
    }

    Vector2f& Vector2f::normalize()
    {
        (*this) *= rsqrt(length2());
        return *this;
    }

    Vector2f& Vector2f::operator+=(const Vector2f& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2f& Vector2f::operator-=(const Vector2f& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2f& Vector2f::operator*=(const Vector2f& v)
    {
       x *= v.x;
       y *= v.y;

        return *this;
    }

    Vector2f& Vector2f::operator/=(const Vector2f& v)
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }
    // vector algebra


    float Vector2f::length() const
    {
        Vector2f copy(*this);
        copy *= copy;
        float sum = copy.x + copy.y;

        return std::sqrt(sum);
    }

    float Vector2f::length2() const
    {
        Vector2f copy(*this);
        copy *= copy;
        float sum = copy.x + copy.y;

        return sum;
    }

    Vector2f operator+(const Vector2f& v, const Vector2f& u)
    {
        return Vector2f(v.x + u.x, v.y + u.y);
    }

    Vector2f operator-(const Vector2f& v, const Vector2f& u)
    {
        return Vector2f(v.x - u.x, v.y - u.y);
    }

    Vector2f operator*(const Vector2f& v, const Vector2f& u)
    {
        return Vector2f(v.x * u.x, v.y * u.y);
    }

    Vector2f operator*(float l, const Vector2f& v)
    {
        return Vector2f(v.x * l, v.y * l);
    }

    Vector2f operator/(const Vector2f& v, const Vector2f& u)
    {
        return Vector2f(v.x / u.x, v.y / u.y);
    }

    Vector2f operator/(float l, const Vector2f& v)
    {
       return Vector2f(l / v.x, l / v.y);
    }

    Vector2f operator/(const Vector2f& v, float l)
    {
        return Vector2f(v.x / l, v.y / l);
    }

    Vector2f operator*(const Vector2f& u, float l)
    {
        return l * u;
    }

    float dotProduct(const Vector2f& v, const Vector2f& u)
    {
        Vector2f prod = v * u;

        float sum = prod.x + prod.y;

        return sum;
    }

    Vector2f normalize(const Vector2f& v)
    {
        Vector2f copy = v;

        return copy.normalize();
    }

    // comparison
    bool operator==(const Vector2f& v, const Vector2f& u)
    {
        return v.x == u.x && 
        v.y == u.y;
    }
    
    bool operator!=(const Vector2f& v, const Vector2f& u)
    {
        return !(v == u);
    }

    // io
    std::ostream& operator<<(std::ostream& stream, const Vector2f& v)
    {
        stream << '(' << v.x << ','
        << v.y << ')';

        return stream;
    }
    
    Vector2f min(const Vector2f& v , const Vector2f& u)
    {
        return Vector2f(std::min(v.x, u.x), std::min(v.y, u.y));
    }
    
    Vector2f max(const Vector2f& v , const Vector2f& u)
    {
        return Vector2f(std::max(v.x, u.x), std::max(v.y, u.y));
    }
    
}
