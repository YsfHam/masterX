#pragma once

#include "Vector3f.hpp"
#include "matrixFomatIO.hpp"
#include "Matrix4f.hpp"


namespace math3D
{

    class Matrix3f
    {
    public:
        Matrix3f(const Vector3f& diag);
        Matrix3f(float l);
        Matrix3f(const std::initializer_list<float>& matrix);
        Matrix3f(const Vector3f& l1, const Vector3f& l2, const Vector3f& l3);
        Matrix3f(const Matrix4f& m);

        Matrix3f& operator+=(const Matrix3f& m);
        Matrix3f& operator-=(const Matrix3f& m);
        Matrix3f& operator*=(const Matrix3f& m);
        Matrix3f& operator*=(float l);
        Matrix3f& operator/=(float l);

        Matrix3f& transpose();
        void transpose(Matrix3f& m) const;
        float& operator()(size_t row, size_t col);
        float operator()(size_t row, size_t col) const;

        float det() const;
        Matrix3f& inverse();

        friend Matrix3f operator+(const Matrix3f& a, const Matrix3f& b);
        friend Matrix3f operator-(const Matrix3f& a, const Matrix3f& b);
        friend Matrix3f operator*(const Matrix3f& a, const Matrix3f& b);
        friend Vector3f operator*(const Matrix3f& a, const Vector3f& v);
        friend Vector3f operator*(const Vector3f& v, const Matrix3f& a);
        friend Matrix3f operator*(const Matrix3f& a, float l);
        friend Matrix3f operator*(float l, const Matrix3f& a);
        friend Matrix3f operator/(const Matrix3f& a, float l);
        

        friend bool operator==(const Matrix3f& a, const Matrix3f& b);
        friend bool operator!=(const Matrix3f& a, const Matrix3f& b);

        friend std::ostream& operator<<(std::ostream& stream, const Matrix3f&);

    public:

        static const Matrix3f Identity;
        static const Matrix3f Zero;

        static MatrixFormat PrintFormat;

    private:
        float m_matrix[9];

    };


    Matrix3f inverse(const Matrix3f& m);



}