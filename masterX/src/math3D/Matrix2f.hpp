#pragma once

#include "Vector2f.hpp"
#include "matrixFomatIO.hpp"
#include "Matrix3f.hpp"
#include "Matrix4f.hpp"


namespace math3D
{

    class Matrix2f
    {
    public:
        Matrix2f(const Vector2f& diag);
        Matrix2f(float l);
        Matrix2f(const std::initializer_list<float>& matrix);
        Matrix2f(const Vector2f& l1, const Vector2f& l2);
        Matrix2f(const Matrix3f& m);
        Matrix2f(const Matrix4f& m);

        Matrix2f& operator+=(const Matrix2f& m);
        Matrix2f& operator-=(const Matrix2f& m);
        Matrix2f& operator*=(const Matrix2f& m);
        Matrix2f& operator*=(float l);
        Matrix2f& operator/=(float l);

        Matrix2f& transpose();
        void transpose(Matrix2f& m) const;
        float& operator()(size_t row, size_t col);
        float operator()(size_t row, size_t col) const;

        float det() const;
        Matrix2f& inverse();

        friend Matrix2f operator+(const Matrix2f& a, const Matrix2f& b);
        friend Matrix2f operator-(const Matrix2f& a, const Matrix2f& b);
        friend Matrix2f operator*(const Matrix2f& a, const Matrix2f& b);
        friend Vector2f operator*(const Matrix2f& a, const Vector2f& v);
        friend Vector2f operator*(const Vector2f& v, const Matrix2f& a);
        friend Matrix2f operator*(const Matrix2f& a, float l);
        friend Matrix2f operator*(float l, const Matrix2f& a);
        friend Matrix2f operator/(const Matrix2f& a, float l);

        friend bool operator==(const Matrix2f& a, const Matrix2f& b);
        friend bool operator!=(const Matrix2f& a, const Matrix2f& b);


        std::ostream& print(std::ostream& stream) const;

    public:

        static const Matrix2f Identity;
        static const Matrix2f Zero;

        static MatrixFormat PrintFormat;

    private:
        float m_matrix[4];

    };

    Matrix2f inverse(const Matrix2f& m);
}