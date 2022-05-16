#include "Matrix2f.hpp"

#include <cstring>
#include <string>
#include <iomanip>

namespace math3D
{
    const Matrix2f Matrix2f::Identity(1.0f);
    const Matrix2f Matrix2f::Zero(0.0f);

    MatrixFormat Matrix2f::PrintFormat = MatrixFormat::NORMAL;


    Matrix2f::Matrix2f(const Vector2f& diag)
    {
        std::memset(m_matrix, 0, sizeof(m_matrix));
        m_matrix[0 * 2 + 0] = diag.x;
        m_matrix[1 * 2 + 1] = diag.y;
    }
    
    Matrix2f::Matrix2f(float l)
    : Matrix2f(Vector2f(l))
    {}

    Matrix2f::Matrix2f(const std::initializer_list<float>& matrix)
    {
        std::copy(matrix.begin(), matrix.end(), m_matrix);
    }

    Matrix2f::Matrix2f(const Vector2f& l1, const Vector2f& l2)
    {
        float *p[3] = { (float*)&l1, (float*)&l2};
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
                m_matrix[i * 2 + j] = p[i][j];
        }
    }

    Matrix2f::Matrix2f(const Matrix3f& m)
    {
        m_matrix[0] = m(0, 0);
        m_matrix[1] = m(0, 1);
        m_matrix[2] = m(1, 0);
        m_matrix[3] = m(1, 1);
    }
    
    Matrix2f::Matrix2f(const Matrix4f& m)
    {
        m_matrix[0] = m(0, 0);
        m_matrix[1] = m(0, 1);
        m_matrix[2] = m(1, 0);
        m_matrix[3] = m(1, 1);
    }

    float& Matrix2f::operator()(size_t row, size_t col)
    {
        return m_matrix[row * 2 + col];
    }

    float Matrix2f::operator()(size_t row, size_t col) const
    {
        return m_matrix[row * 2 + col];
    }

    Matrix2f& Matrix2f::operator+=(const Matrix2f& m)
    {
        m_matrix[0] += m.m_matrix[0];
        m_matrix[1] += m.m_matrix[1];
        m_matrix[2] += m.m_matrix[2];
        m_matrix[3] += m.m_matrix[3];
        return *this;
    }

    Matrix2f& Matrix2f::operator-=(const Matrix2f& m)
    {
        m_matrix[0] -= m.m_matrix[0];
        m_matrix[1] -= m.m_matrix[1];
        m_matrix[2] -= m.m_matrix[2];
        m_matrix[3] -= m.m_matrix[3];
        return *this;
    }

    Matrix2f& Matrix2f::operator*=(const Matrix2f& m)
    {
        Matrix2f transpose_m = Matrix2f::Zero;
        m.transpose(transpose_m);


        float *row0 = m_matrix;
        float *row1 = m_matrix + 2;

        float *m_col0 = transpose_m.m_matrix;
        float *m_col1 = transpose_m.m_matrix + 2;

        float res_row0[2], res_row1[2];

        res_row0[0] = row0[0] * m_col0[0] + row0[1] * m_col0[1];
        res_row0[1] = row0[0] * m_col1[0] + row0[1] * m_col1[1];
        res_row1[0] = row1[0] * m_col0[0] + row0[1] * m_col0[1];
        res_row1[1] = row1[0] * m_col1[0] + row1[1] * m_col1[1];

        m_matrix[0] = res_row0[0];
        m_matrix[1] = res_row0[1];
        m_matrix[2] = res_row1[0];
        m_matrix[3] = res_row1[1];

        return *this;
    }

    Matrix2f& Matrix2f::operator*=(float l)
    {
        m_matrix[0] *= l;
        m_matrix[1] *= l;
        m_matrix[2] *= l;
        m_matrix[3] *= l;
        return *this;
    }

    Matrix2f& Matrix2f::operator/=(float l)
    {
        m_matrix[0] /= l;
        m_matrix[1] /= l;
        m_matrix[2] /= l;
        m_matrix[3] /= l;

        return *this;
    }

    Matrix2f& Matrix2f::transpose()
    {
        float temp = m_matrix[1];
        m_matrix[1] = m_matrix[2];
        m_matrix[2] = temp;

        return *this;
    }
    
    void Matrix2f::transpose(Matrix2f& m) const
    {
       m = *this;
       m.transpose();
    }

    float Matrix2f::det() const
    {
        return m_matrix[0] * m_matrix[3] - m_matrix[2] * m_matrix[1];
    }

    Matrix2f& Matrix2f::inverse()
    {
        float Det = det();
        if (Det == 0.0f)
            return *this;

        float temp = m_matrix[0];
        m_matrix[0] = m_matrix[3];
        m_matrix[3] = temp;

        m_matrix[2] *= -1;
        m_matrix[1] *= -1;

        (*this) /= Det;

        return *this;

    }

    Matrix2f operator+(const Matrix2f& a, const Matrix2f& b)
    {
        Matrix2f result(0.0f);
        for (int i = 0; i < 4; i++)
            result.m_matrix[i] = a.m_matrix[i] + b.m_matrix[i];
        return result;
    }

    Matrix2f operator-(const Matrix2f& a, const Matrix2f& b)
    {
        Matrix2f result(0.0f);

        for (int i = 0; i < 4; i++)
            result.m_matrix[i] = a.m_matrix[i] - b.m_matrix[i];
        return result;
    }

    Matrix2f operator*(const Matrix2f& a, const Matrix2f& b)
    {
        Matrix2f trans_b(0.0f);
        b.transpose(trans_b);

        Matrix2f result(0.0f);

        float *a_row0 = (float*)a.m_matrix;
        float *a_row1 = (float*)a.m_matrix + 2;

        float *b_col0 = trans_b.m_matrix;
        float *b_col1 = trans_b.m_matrix + 2;

        float res_row0[2], res_row1[2];

        res_row0[0] = a_row0[0] * b_col0[0] + a_row0[1] * b_col0[1];
        res_row0[1] = a_row0[0] * b_col1[0] + a_row0[1] * b_col1[1];
        res_row1[0] = a_row1[0] * b_col0[0] + a_row0[1] * b_col0[1];
        res_row1[1] = a_row1[0] * b_col1[0] + a_row1[1] * b_col1[1];

        result.m_matrix[0] = res_row0[0];
        result.m_matrix[1] = res_row0[1];
        result.m_matrix[2] = res_row1[0];
        result.m_matrix[3] = res_row1[1];

        return result;
    }

    Vector2f operator*(const Matrix2f& a, const Vector2f& v)
    {
        const float *a_row0 = a.m_matrix;
        const float *a_row1 = a.m_matrix + 2;

        Vector2f result = Vector2f::Zero;

        result.x = a_row0[0] * v.x + a_row0[1] * v.y;
        result.y = a_row1[0] * v.x + a_row1[1] * v.y;

        return result;

    }

    Vector2f operator*(const Vector2f& v, const Matrix2f& a)
    {
        Matrix2f a_transpose = Matrix2f::Zero;
        a.transpose(a_transpose);
        return a_transpose * v;
    }

    Matrix2f operator*(const Matrix2f& a, float l)
    {

        Matrix2f res(0.0f);

        for (int i = 0; i < 4; i++)
            res.m_matrix[i] = a.m_matrix[i] * l;

        return res;
    }

    Matrix2f operator*(float l, const Matrix2f& a)
    {
        return a * l;
    }

    Matrix2f operator/(const Matrix2f& a, float l)
    {
        Matrix2f res(0.0f);

        for (int i = 0; i < 4; i++)
            res.m_matrix[i] = a.m_matrix[i] / l;


        return res;
    }

    bool operator==(const Matrix2f& a, const Matrix2f& b)
    {
       return a.m_matrix[0] == b.m_matrix[0] &&
                a.m_matrix[1] == b.m_matrix[1] &&
                a.m_matrix[2] == b.m_matrix[2] &&
                a.m_matrix[3] == b.m_matrix[3];

    }
    
    bool operator!=(const Matrix2f& a, const Matrix2f& b)
    {
        return !(a == b);
    }

    std::ostream& Matrix2f::print(std::ostream& stream) const
    {
        const Matrix2f& m = *this;
        int maxWidth = 0;
        if (Matrix2f::PrintFormat == MatrixFormat::BEUTIFY)
        {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    std::string str = std::to_string(m(i, j));
                    if (str.size() > maxWidth)
                        maxWidth = str.size();
                }
            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if (maxWidth != 0)
                    stream << std::setw(maxWidth);
                stream << m(i, j) << ' ';
            }
            stream << std::endl;
        }

        stream << std::setw(0);

        return stream;
    }

    Matrix2f inverse(const Matrix2f& m)
    {
        Matrix2f copy(m);

        return copy.inverse();
    }
}