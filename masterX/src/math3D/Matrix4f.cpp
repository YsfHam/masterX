#include "Matrix4f.hpp"

#include <cstring>
#include <string>
#include <iomanip>

#ifdef USE_INTRINSICS
    #include "simd/sse/Matrix4f_sse.inl"
#endif

namespace math3D
{
    const Matrix4f Matrix4f::Identity(1.0f);
    const Matrix4f Matrix4f::Zero(0.0f);

    MatrixFormat Matrix4f::PrintFormat = MatrixFormat::NORMAL;


    Matrix4f::Matrix4f(const Vector4f& diag)
    {
        std::memset(m_matrix, 0, sizeof(m_matrix));
        m_matrix[0 * 4 + 0] = diag.x;
        m_matrix[1 * 4 + 1] = diag.y;
        m_matrix[2 * 4 + 2] = diag.z;
        m_matrix[3 * 4 + 3] = diag.w;
    }
    
    Matrix4f::Matrix4f(float l)
    : Matrix4f(Vector4f(l))
    {}

    Matrix4f::Matrix4f(const std::initializer_list<float>& matrix)
    {
        std::copy(matrix.begin(), matrix.end(), m_matrix);
    }

    Matrix4f::Matrix4f(const Vector4f& l1, const Vector4f& l2, const Vector4f& l3, const Vector4f& l4)
    {
        float *p[4] = { (float*)&l1, (float*)&l2, (float*)&l3, (float*)&l4};
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                m_matrix[i * 4 + j] = p[i][j];
        }
    }

    Matrix4f inverse(const Matrix4f& m)
    {
        Matrix4f copy(m);

        return copy.inverse();
    }

    float& Matrix4f::operator()(size_t row, size_t col)
    {
        return m_matrix[row * 4 + col];
    }

    float Matrix4f::operator()(size_t row, size_t col) const
    {
        return m_matrix[row * 4 + col];
    }

    std::ostream& Matrix4f::print(std::ostream& stream) const
    {
        const Matrix4f& m = *this;
        int maxWidth = 0;
        if (Matrix4f::PrintFormat == MatrixFormat::BEUTIFY)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::string str = std::to_string(m(i, j));
                    if (str.size() > maxWidth)
                        maxWidth = str.size();
                }
            }
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
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