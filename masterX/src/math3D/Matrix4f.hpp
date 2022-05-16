#pragma once

#include "Vector4f.hpp"
#include "matrixFomatIO.hpp"

namespace math3D
{
    class Matrix4f
    {
    public:
        Matrix4f(const Vector4f& diag);
        Matrix4f(float l);
        Matrix4f(const std::initializer_list<float>& matrix);
        Matrix4f(const Vector4f& l1, const Vector4f& l2, const Vector4f& l3, const Vector4f& l4);

        Matrix4f& operator+=(const Matrix4f& m);
        Matrix4f& operator-=(const Matrix4f& m);
        Matrix4f& operator*=(const Matrix4f& m);
        Matrix4f& operator*=(float l);
        Matrix4f& operator/=(float l);

        Matrix4f& transpose();
        void transpose(Matrix4f& m) const;
        float& operator()(size_t row, size_t col);
        float operator()(size_t row, size_t col) const;

        float det() const;
        Matrix4f& inverse();

        friend Matrix4f operator+(const Matrix4f& a, const Matrix4f& b);
        friend Matrix4f operator-(const Matrix4f& a, const Matrix4f& b);
        friend Matrix4f operator*(const Matrix4f& a, const Matrix4f& b);
        friend Vector4f operator*(const Matrix4f& a, const Vector4f& v);
        friend Vector4f operator*(const Vector4f& v, const Matrix4f& a);
        friend Matrix4f operator*(const Matrix4f& a, float l);
        friend Matrix4f operator*(float l, const Matrix4f& a);
        friend Matrix4f operator/(const Matrix4f& a, float l);

        friend bool operator==(const Matrix4f& a, const Matrix4f& b);
        friend bool operator!=(const Matrix4f& a, const Matrix4f& b);


        std::ostream& print(std::ostream& stream) const;


    public:

        static const Matrix4f Identity;
        static const Matrix4f Zero;

        static MatrixFormat PrintFormat;

    private:
        float m_matrix[16];

    };

    Matrix4f inverse(const Matrix4f& m);



}