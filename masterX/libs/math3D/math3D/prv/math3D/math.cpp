#include "math.hpp"

#include "Quaternion.hpp"

namespace math3D
{

    const float Angle::DEGREES_2_RADIANS_RATIO = M_PI / 180.0f;
    const float Angle::DEGREES_2_HALF_RADIANS_RATIO = M_PI_2 / 180.0f;
    const float Angle::RADIANS_2_DEGREES_RATIO = 180.0f * M_1_PI;


    Matrix4f scale(const Matrix4f& matrix, const Vector3f scale)
    {
        Matrix4f scaleMat = Vector4f(scale);

        return matrix * scaleMat;
    }

    Matrix4f translate(const Matrix4f& matrix, const Vector3f translation)
    {
        Matrix4f translationMat = Matrix4f::Identity;

        translationMat(0, 3) = translation.x;
        translationMat(1, 3) = translation.y;
        translationMat(2, 3) = translation.z;

        return matrix * translationMat;
    }

    Vector3f rotate(const Vector3f& v, const Angle& angle, const Vector3f& axis)
    {
        float theta = angle.RadiansHalf;
        float cosTheta = std::cos(theta);
        float sinTheta = std::sin(theta);

        Quaternion quat(cosTheta, axis * sinTheta);
        Quaternion quatV(0.0f, v);

        return (quat * quatV * conjugate(quat)).getImaginary();
    }
}