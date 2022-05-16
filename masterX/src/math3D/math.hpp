#pragma once
#include "Matrix4f.hpp"
#include "Matrix3f.hpp"


#include <cmath>


// This will contain useful math functions used for graphics, physics, etc
namespace math3D
{
    struct Angle
    {
        float Degrees;
        float Radians;
        float RadiansHalf;

        static const float DEGREES_2_RADIANS_RATIO;
        static const float DEGREES_2_HALF_RADIANS_RATIO;
        static const float RADIANS_2_DEGREES_RATIO;

        Angle(float degrees)
            :Degrees(degrees), 
            Radians(degrees * DEGREES_2_RADIANS_RATIO),
            RadiansHalf(degrees * DEGREES_2_HALF_RADIANS_RATIO)
        {}

        Angle(const Angle&) = default;
        Angle(Angle&&) = default;
        Angle& operator=(const Angle& a)
        {
            Degrees = a.Degrees;
            Radians = a.Radians;
            RadiansHalf = a.RadiansHalf;

            return *this;
        }
    };

    // general math functions
    template<typename T>
    T rsqrt(T number)
    {
        using std::sqrt;
        return sqrt(number) / number;
    }

    template<typename T>
    T clamp(T val, T minVal, T maxVal)
    {
        using std::max;
        using std::min;
        return max(minVal, min(maxVal, val));
    }

    // graphics functions

    Matrix4f scale(const Matrix4f& matrix, const Vector3f scale);
    Matrix4f translate(const Matrix4f& matrix, const Vector3f translation);
    Matrix4f rotate(const Matrix4f& matrix, const Angle& angle, const Vector3f axis);

    Matrix3f scale2D(const Matrix3f& matrix, const Vector2f scale);
    Matrix3f translate2D(const Matrix3f& matrix, const Vector2f translation);
    Matrix3f rotate2D(const Matrix3f& matrix, const Angle& angle);

    Vector3f rotate(const Vector3f& v, const Angle& angle, const Vector3f& axis);

    Matrix4f orthographic(float left, float right, float top, float bottom, float near, float far);
    Matrix3f orthographic2D(float left, float right, float top, float bottom);
}
