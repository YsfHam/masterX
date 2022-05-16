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

    Matrix4f rotate(const Matrix4f& matrix, const Angle& angle, const Vector3f axis)
    {
        float theta = angle.RadiansHalf;
        float cosTheta = std::cos(theta);
        float sinTheta = std::sin(theta);

        Quaternion quat(cosTheta, axis * sinTheta);

        float s = quat.getReal();
        float x = quat.getImaginary().x;
        float y = quat.getImaginary().y;
        float z = quat.getImaginary().z;

        float x2 = x * x;
        float y2 = y * y;
        float z2 = z * z;

        Matrix4f rotationMatrix({
            1.0f - 2.0f*y2 - 2.0f*z2, 2*x*y - 2*s*z, 2*x*z + 2*s*y, 0,
            2*x*y + 2*s*z, 1 - 2*x2 - 2*z2, 2*y*z - 2*s*x, 0,
            2*x*z - 2*s*y, 2*y*z+2*s*x, 1 - 2*x2 - 2*y2, 0,
            0, 0, 0, 1
        });

        return matrix * rotationMatrix;

    }


    Matrix3f scale2D(const Matrix3f& matrix, const Vector2f scale)
    {
        Matrix3f scaleMat = Vector3f(scale, 1.f);

        return matrix * scaleMat;
    }

    Matrix3f translate2D(const Matrix3f& matrix, const Vector2f translation)
    {
        Matrix3f translationMat = Matrix3f::Identity;

        translationMat(0, 2) = translation.x;
        translationMat(1, 2) = translation.y;

        return matrix * translationMat;
    }

    Matrix3f rotate2D(const Matrix3f& matrix, const Angle& angle)
    {
        float theta = angle.RadiansHalf;
        float cosTheta = std::cos(theta);
        float sinTheta = std::sin(theta);
        Vector3f axis(0.0f, 0.0f, 1.0f);
        Quaternion quat(cosTheta, axis * sinTheta);

        float s = quat.getReal();
        float z = quat.getImaginary().z;

        float z2 = z * z;

        Matrix3f rotationMatrix({
            1.0f - 2.0f*z2, - 2*s*z,  0,
            2*s*z,          1 - 2*z2, 0,
            0,              0,        1
            //0, 0, 0, 1
        });

        return matrix * rotationMatrix;
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

    Matrix4f orthographic(float left, float right, float top, float bottom, float near, float far)
    {
        float width = right - left;
        float height = top - bottom;
        float depth = far - near;

        return Matrix4f({
            2.0f / width, 0, 0, -(right+left)/width,
            0, 2.0f / height, 0, -(top + bottom) / height,
            0, 0, 2.0f / depth, -(far + near) / depth,
            0, 0, 0, 1
        });
    }

    Matrix3f orthographic2D(float left, float right, float top, float bottom)
    {
        float width = right - left;
        float height = top - bottom;

        return Matrix3f({
            2.0f / width, 0,            -(right+left)/width,
            0,           2.0f / height, -(top + bottom) / height,
            0,            0,            1
        });
    }
}