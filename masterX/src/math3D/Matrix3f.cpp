#include "Matrix3f.hpp"

#include <cstring>
#include <string>
#include <iomanip>

#ifdef USE_INTRINSICS
    #include "simd/sse/Matrix3f_sse.inl"
#endif

namespace math3D
{
    const Matrix3f Matrix3f::Identity(1.0f);
    const Matrix3f Matrix3f::Zero(0.0f);

    MatrixFormat Matrix3f::PrintFormat = MatrixFormat::NORMAL;


    Matrix3f::Matrix3f(const Vector3f& diag)
    {
        std::memset(m_matrix, 0, sizeof(m_matrix));
        m_matrix[0 * 3 + 0] = diag.x;
        m_matrix[1 * 3 + 1] = diag.y;
        m_matrix[2 * 3 + 2] = diag.z;
    }
    
    Matrix3f::Matrix3f(float l)
    : Matrix3f(Vector3f(l))
    {}

    Matrix3f::Matrix3f(const std::initializer_list<float>& matrix)
    {
        std::copy(matrix.begin(), matrix.end(), m_matrix);
    }

    Matrix3f::Matrix3f(const Vector3f& l1, const Vector3f& l2, const Vector3f& l3)
    {
        float *p[3] = { (float*)&l1, (float*)&l2, (float*)&l3};
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                m_matrix[i * 3 + j] = p[i][j];
        }
    }

    Matrix3f::Matrix3f(const Matrix4f& m)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                m_matrix[i * 3 + j] = m(i, j);
        }
    }

    Matrix3f inverse(const Matrix3f& m)
    {
        Matrix3f copy(m);

        return copy.inverse();
    }

    float& Matrix3f::operator()(size_t row, size_t col)
    {
        return m_matrix[row * 3 + col];
    }

    float Matrix3f::operator()(size_t row, size_t col) const
    {
        return m_matrix[row * 3 + col];
    }

    std::ostream& Matrix3f::print(std::ostream& stream) const
    {
        const Matrix3f& m = *this;
        int maxWidth = 0;
        if (Matrix3f::PrintFormat == MatrixFormat::BEUTIFY)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    std::string str = std::to_string(m(i, j));
                    if (str.size() > maxWidth)
                        maxWidth = str.size();
                }
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
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
}