#include "math3D/Matrix4f.hpp"
#include "helpers.hpp"

static void buildMatrix(float *matrix, __m128 row0, __m128 row1, __m128 row2, __m128 row3) 
{
    matrix[0 * 4 + 0] = row0[0];
    matrix[0 * 4 + 1] = row0[1];
    matrix[0 * 4 + 2] = row0[2];
    matrix[0 * 4 + 3] = row0[3];

    matrix[1 * 4 + 0] = row1[0];
    matrix[1 * 4 + 1] = row1[1];
    matrix[1 * 4 + 2] = row1[2];
    matrix[1 * 4 + 3] = row1[3];

    matrix[2 * 4 + 0] = row2[0];
    matrix[2 * 4 + 1] = row2[1];
    matrix[2 * 4 + 2] = row2[2];
    matrix[2 * 4 + 3] = row2[3];

    matrix[3 * 4 + 0] = row3[0];
    matrix[3 * 4 + 1] = row3[1];
    matrix[3 * 4 + 2] = row3[2];
    matrix[3 * 4 + 3] = row3[3];
}

namespace math3D
{
    Matrix4f& Matrix4f::operator+=(const Matrix4f& m)
    {
        __m128 _row0 = mm_load_ps(m_matrix + 4 * 0);
        __m128 _row1 = mm_load_ps(m_matrix + 4 * 1);
        __m128 _row2 = mm_load_ps(m_matrix + 4 * 2);
        __m128 _row3 = mm_load_ps(m_matrix + 4 * 3);

        __m128 _m_row0 = mm_load_ps(m.m_matrix + 4 * 0);
        __m128 _m_row1 = mm_load_ps(m.m_matrix + 4 * 1);
        __m128 _m_row2 = mm_load_ps(m.m_matrix + 4 * 2);
        __m128 _m_row3 = mm_load_ps(m.m_matrix + 4 * 3);

        _row0 = _mm_add_ps(_row0, _m_row0);
        _row1 = _mm_add_ps(_row1, _m_row1);
        _row2 = _mm_add_ps(_row2, _m_row2);
        _row3 = _mm_add_ps(_row3, _m_row3);

        buildMatrix(m_matrix, _row0, _row1, _row2, _row3);

        return *this;
    }

    Matrix4f& Matrix4f::operator-=(const Matrix4f& m)
    {
        __m128 _row0 = mm_load_ps(m_matrix + 4 * 0);
        __m128 _row1 = mm_load_ps(m_matrix + 4 * 1);
        __m128 _row2 = mm_load_ps(m_matrix + 4 * 2);
        __m128 _row3 = mm_load_ps(m_matrix + 4 * 3);

        __m128 _m_row0 = mm_load_ps(m.m_matrix + 4 * 0);
        __m128 _m_row1 = mm_load_ps(m.m_matrix + 4 * 1);
        __m128 _m_row2 = mm_load_ps(m.m_matrix + 4 * 2);
        __m128 _m_row3 = mm_load_ps(m.m_matrix + 4 * 3);

        _row0 = _mm_sub_ps(_row0, _m_row0);
        _row1 = _mm_sub_ps(_row1, _m_row1);
        _row2 = _mm_sub_ps(_row2, _m_row2);
        _row3 = _mm_sub_ps(_row3, _m_row3);

        buildMatrix(m_matrix, _row0, _row1, _row2, _row3);

        return *this;
    }

    Matrix4f& Matrix4f::operator*=(const Matrix4f& m)
    {
        Matrix4f trans_m(0.0f);
        m.transpose(trans_m);

        __m128 _row0 = mm_load_ps(m_matrix + 4 * 0);
        __m128 _row1 = mm_load_ps(m_matrix + 4 * 1);
        __m128 _row2 = mm_load_ps(m_matrix + 4 * 2);
        __m128 _row3 = mm_load_ps(m_matrix + 4 * 3);

        __m128 _m_col0 = mm_load_ps(trans_m.m_matrix + 4 * 0);
        __m128 _m_col1 = mm_load_ps(trans_m.m_matrix + 4 * 1);
        __m128 _m_col2 = mm_load_ps(trans_m.m_matrix + 4 * 2);
        __m128 _m_col3 = mm_load_ps(trans_m.m_matrix + 4 * 3);

        __m128 _res0, _res1, _res2, _res3, _temp;

        _temp = _mm_mul_ps(_row0, _m_col0);
        _res0[0] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row0, _m_col1);
        _res0[1] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row0, _m_col2);
        _res0[2] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row0, _m_col3);
        _res0[3] = _temp[0] + _temp[1] + _temp[2] + _temp[3];

        _temp = _mm_mul_ps(_row1, _m_col0);
        _res1[0] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row1, _m_col1);
        _res1[1] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row1, _m_col2);
        _res1[2] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row1, _m_col3);
        _res1[3] = _temp[0] + _temp[1] + _temp[2] + _temp[3];

        _temp = _mm_mul_ps(_row2, _m_col0);
        _res2[0] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row2, _m_col1);
        _res2[1] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row2, _m_col2);
        _res2[2] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row2, _m_col3);
        _res2[3] = _temp[0] + _temp[1] + _temp[2] + _temp[3];

        _temp = _mm_mul_ps(_row3, _m_col0);
        _res3[0] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row3, _m_col1);
        _res3[1] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row3, _m_col2);
        _res3[2] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_row3, _m_col3);
        _res3[3] = _temp[0] + _temp[1] + _temp[2] + _temp[3];

        buildMatrix(m_matrix, _res0, _res1, _res2, _res3);


        return *this;
    }

    Matrix4f& Matrix4f::operator*=(float l)
    {
        float lVec[] = {l, l, l, l};

        __m128 _row0 = mm_load_ps(m_matrix + 4 * 0);
        __m128 _row1 = mm_load_ps(m_matrix + 4 * 1);
        __m128 _row2 = mm_load_ps(m_matrix + 4 * 2);
        __m128 _row3 = mm_load_ps(m_matrix + 4 * 3);

        __m128 _lVec = mm_load_ps(lVec);

        _row0 = _mm_mul_ps(_row0, _lVec);
        _row1 = _mm_mul_ps(_row1, _lVec);
        _row2 = _mm_mul_ps(_row2, _lVec);
        _row3 = _mm_mul_ps(_row3, _lVec);

        buildMatrix(m_matrix, _row0, _row1, _row2, _row3);

        return *this;
    }

    Matrix4f& Matrix4f::operator/=(float l)
    {
        float lVec[] = {l, l, l, l};

        __m128 _row0 = mm_load_ps(m_matrix + 4 * 0);
        __m128 _row1 = mm_load_ps(m_matrix + 4 * 1);
        __m128 _row2 = mm_load_ps(m_matrix + 4 * 2);
        __m128 _row3 = mm_load_ps(m_matrix + 4 * 3);

        __m128 _lVec = mm_load_ps(lVec);

        _row0 = _mm_div_ps(_row0, _lVec);
        _row1 = _mm_div_ps(_row1, _lVec);
        _row2 = _mm_div_ps(_row2, _lVec);
        _row3 = _mm_div_ps(_row3, _lVec);

        buildMatrix(m_matrix, _row0, _row1, _row2, _row3);

        return *this;
    }

    Matrix4f& Matrix4f::transpose()
    {
        __m128 _row0 = mm_load_ps(m_matrix + 4 * 0);
        __m128 _row1 = mm_load_ps(m_matrix + 4 * 1);
        __m128 _row2 = mm_load_ps(m_matrix + 4 * 2);
        __m128 _row3 = mm_load_ps(m_matrix + 4 * 3);

        _MM_TRANSPOSE4_PS(_row0, _row1, _row2, _row3);
        buildMatrix(m_matrix, _row0, _row1, _row2, _row3);

        return *this;
    }
    
    void Matrix4f::transpose(Matrix4f& m) const
    {
        __m128 _row0 = mm_load_ps(m_matrix + 4 * 0);
        __m128 _row1 = mm_load_ps(m_matrix + 4 * 1);
        __m128 _row2 = mm_load_ps(m_matrix + 4 * 2);
        __m128 _row3 = mm_load_ps(m_matrix + 4 * 3);

        _MM_TRANSPOSE4_PS(_row0, _row1, _row2, _row3);

        buildMatrix(m.m_matrix, _row0, _row1, _row2, _row3);
    }

    float Matrix4f::det() const
    {
        __m128 _rows[4] = {
            mm_load_ps(m_matrix + 4 * 0),
            mm_load_ps(m_matrix + 4 * 1),
            mm_load_ps(m_matrix + 4 * 2),
            mm_load_ps(m_matrix + 4 * 3),
        };

        for (int i = 0; i < 4; i++)
        {
            if (_rows[i][i] == 0.0f)
                return 0.0f;
            for (int j = i + 1; j < 4; j++)
            {
                float c = _rows[j][i] / _rows[i][i];
                float cVec[] = {c, c, c, c};
                __m128 _cVec = mm_load_ps(cVec);
                _rows[j] = _mm_sub_ps(_rows[j], _mm_mul_ps(_cVec, _rows[i]));
            }
        }

        return _rows[0][0] * _rows[1][1] * _rows[2][2] * _rows[3][3];
    }

    Matrix4f& Matrix4f::inverse()
    {
        if (det() == 0.0f)
            return *this;

        const Matrix4f& id = Matrix4f::Identity;

         __m128 _rows[4] = {
            mm_load_ps(m_matrix + 4 * 0),
            mm_load_ps(m_matrix + 4 * 1),
            mm_load_ps(m_matrix + 4 * 2),
            mm_load_ps(m_matrix + 4 * 3),
        };

        __m128 _id_rows[4] = {
            mm_load_ps(id.m_matrix + 4 * 0),
            mm_load_ps(id.m_matrix + 4 * 1),
            mm_load_ps(id.m_matrix + 4 * 2),
            mm_load_ps(id.m_matrix + 4 * 3),
        };

        for (int i = 0; i < 4; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                float c = _rows[j][i] / _rows[i][i];
                float cVec[] = {c, c, c, c};
                __m128 _cVec = mm_load_ps(cVec);
                _rows[j] = _mm_sub_ps(_rows[j], _mm_mul_ps(_cVec, _rows[i]));
                _id_rows[j] = _mm_sub_ps(_id_rows[j], _mm_mul_ps(_cVec, _id_rows[i]));
            }

            for (int j = 0; j < i; j++)
            {
                float c = _rows[j][i] / _rows[i][i];
                float cVec[] = {c, c, c, c};
                __m128 _cVec = mm_load_ps(cVec);
                _rows[j] = _mm_sub_ps(_rows[j], _mm_mul_ps(_cVec, _rows[i]));
                _id_rows[j] = _mm_sub_ps(_id_rows[j], _mm_mul_ps(_cVec, _id_rows[i]));
            }

            float diag[] = {_rows[i][i], _rows[i][i], _rows[i][i], _rows[i][i]};
            __m128 _diag = mm_load_ps(diag);
            _rows[i] = _mm_div_ps(_rows[i], _diag);
            _id_rows[i] = _mm_div_ps(_id_rows[i], _diag);
        }

        buildMatrix(m_matrix, _id_rows[0], _id_rows[1], _id_rows[2], _id_rows[3]);

        return *this;

    }

    Matrix4f operator+(const Matrix4f& a, const Matrix4f& b)
    {
        Matrix4f result(0.0f);

        __m128 _a_row0 = mm_load_ps(a.m_matrix + 4 * 0);
        __m128 _a_row1 = mm_load_ps(a.m_matrix + 4 * 1);
        __m128 _a_row2 = mm_load_ps(a.m_matrix + 4 * 2);
        __m128 _a_row3 = mm_load_ps(a.m_matrix + 4 * 3);

        __m128 _b_row0 = mm_load_ps(b.m_matrix + 4 * 0);
        __m128 _b_row1 = mm_load_ps(b.m_matrix + 4 * 1);
        __m128 _b_row2 = mm_load_ps(b.m_matrix + 4 * 2);
        __m128 _b_row3 = mm_load_ps(b.m_matrix + 4 * 3);

        __m128 _row0, _row1, _row2, _row3;

        _row0 = _mm_add_ps(_a_row0, _b_row0);
        _row1 = _mm_add_ps(_a_row1, _b_row1);
        _row2 = _mm_add_ps(_a_row2, _b_row2);
        _row3 = _mm_add_ps(_a_row3, _b_row3);

        buildMatrix(result.m_matrix, _row0, _row1, _row2, _row3);
        return result;
    }

    Matrix4f operator-(const Matrix4f& a, const Matrix4f& b)
    {
        Matrix4f result(0.0f);

        __m128 _a_row0 = mm_load_ps(a.m_matrix + 4 * 0);
        __m128 _a_row1 = mm_load_ps(a.m_matrix + 4 * 1);
        __m128 _a_row2 = mm_load_ps(a.m_matrix + 4 * 2);
        __m128 _a_row3 = mm_load_ps(a.m_matrix + 4 * 3);

        __m128 _b_row0 = mm_load_ps(b.m_matrix + 4 * 0);
        __m128 _b_row1 = mm_load_ps(b.m_matrix + 4 * 1);
        __m128 _b_row2 = mm_load_ps(b.m_matrix + 4 * 2);
        __m128 _b_row3 = mm_load_ps(b.m_matrix + 4 * 3);

        __m128 _row0, _row1, _row2, _row3;

        _row0 = _mm_sub_ps(_a_row0, _b_row0);
        _row1 = _mm_sub_ps(_a_row1, _b_row1);
        _row2 = _mm_sub_ps(_a_row2, _b_row2);
        _row3 = _mm_sub_ps(_a_row3, _b_row3);

        buildMatrix(result.m_matrix, _row0, _row1, _row2, _row3);
        return result;
    }

    Matrix4f operator*(const Matrix4f& a, const Matrix4f& b)
    {
        Matrix4f trans_b(0.0f);
        b.transpose(trans_b);

        Matrix4f result(0.0f);

        __m128 _a_row0 = mm_load_ps(a.m_matrix + 4 * 0);
        __m128 _a_row1 = mm_load_ps(a.m_matrix + 4 * 1);
        __m128 _a_row2 = mm_load_ps(a.m_matrix + 4 * 2);
        __m128 _a_row3 = mm_load_ps(a.m_matrix + 4 * 3);

        __m128 _b_col0 = mm_load_ps(trans_b.m_matrix + 4 * 0);
        __m128 _b_col1 = mm_load_ps(trans_b.m_matrix + 4 * 1);
        __m128 _b_col2 = mm_load_ps(trans_b.m_matrix + 4 * 2);
        __m128 _b_col3 = mm_load_ps(trans_b.m_matrix + 4 * 3);

        __m128 _res0, _res1, _res2, _res3, _temp;

        _temp = _mm_mul_ps(_a_row0, _b_col0);
        _res0[0] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row0, _b_col1);
        _res0[1] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row0, _b_col2);
        _res0[2] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row0, _b_col3);
        _res0[3] = _temp[0] + _temp[1] + _temp[2] + _temp[3];

        _temp = _mm_mul_ps(_a_row1, _b_col0);
        _res1[0] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row1, _b_col1);
        _res1[1] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row1, _b_col2);
        _res1[2] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row1, _b_col3);
        _res1[3] = _temp[0] + _temp[1] + _temp[2] + _temp[3];

        _temp = _mm_mul_ps(_a_row2, _b_col0);
        _res2[0] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row2, _b_col1);
        _res2[1] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row2, _b_col2);
        _res2[2] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row2, _b_col3);
        _res2[3] = _temp[0] + _temp[1] + _temp[2] + _temp[3];

        _temp = _mm_mul_ps(_a_row3, _b_col0);
        _res3[0] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row3, _b_col1);
        _res3[1] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row3, _b_col2);
        _res3[2] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row3, _b_col3);
        _res3[3] = _temp[0] + _temp[1] + _temp[2] + _temp[3];

        buildMatrix(result.m_matrix, _res0, _res1, _res2, _res3);

        return result;
    }

    Vector4f operator*(const Matrix4f& a, const Vector4f& v)
    {
        __m128 _a_row0 = mm_load_ps(a.m_matrix + 4 * 0);
        __m128 _a_row1 = mm_load_ps(a.m_matrix + 4 * 1);
        __m128 _a_row2 = mm_load_ps(a.m_matrix + 4 * 2);
        __m128 _a_row3 = mm_load_ps(a.m_matrix + 4 * 3);

        __m128 _v = mm_load_ps((float*)&v);

        __m128 _res, _temp;

        _temp = _mm_mul_ps(_a_row0, _v);
        _res[0] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row1, _v);
        _res[1] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row2, _v);
        _res[2] = _temp[0] + _temp[1] + _temp[2] + _temp[3];
        _temp = _mm_mul_ps(_a_row3, _v);
        _res[3] = _temp[0] + _temp[1] + _temp[2] + _temp[3];

        return Vector4f(_res[0], _res[1], _res[2], _res[3]);

    }

    Vector4f operator*(const Vector4f& v, const Matrix4f& a)
    {
        return a * v;
    }

    Matrix4f operator*(const Matrix4f& a, float l)
    {
        float lVec[] = {l, l, l, l};

        Matrix4f res(0.0f);

        __m128 _row0 = mm_load_ps(a.m_matrix + 4 * 0);
        __m128 _row1 = mm_load_ps(a.m_matrix + 4 * 1);
        __m128 _row2 = mm_load_ps(a.m_matrix + 4 * 2);
        __m128 _row3 = mm_load_ps(a.m_matrix + 4 * 3);

        __m128 _lVec = mm_load_ps(lVec);

        _row0 = _mm_mul_ps(_row0, _lVec);
        _row1 = _mm_mul_ps(_row1, _lVec);
        _row2 = _mm_mul_ps(_row2, _lVec);
        _row3 = _mm_mul_ps(_row3, _lVec);

        buildMatrix(res.m_matrix, _row0, _row1, _row2, _row3);

        return res;
    }

    Matrix4f operator*(float l, const Matrix4f& a)
    {
        return a * l;
    }

    Matrix4f operator/(const Matrix4f& a, float l)
    {
         float lVec[] = {l, l, l, l};

        Matrix4f res(0.0f);

        __m128 _row0 = mm_load_ps(a.m_matrix + 4 * 0);
        __m128 _row1 = mm_load_ps(a.m_matrix + 4 * 1);
        __m128 _row2 = mm_load_ps(a.m_matrix + 4 * 2);
        __m128 _row3 = mm_load_ps(a.m_matrix + 4 * 3);

        __m128 _lVec = mm_load_ps(lVec);

        _row0 = _mm_div_ps(_row0, _lVec);
        _row1 = _mm_div_ps(_row1, _lVec);
        _row2 = _mm_div_ps(_row2, _lVec);
        _row3 = _mm_div_ps(_row3, _lVec);

        buildMatrix(res.m_matrix, _row0, _row1, _row2, _row3);

        return res;
    }

    bool operator==(const Matrix4f& a, const Matrix4f& b)
    {
        __m128 _a_row0 = mm_load_ps(a.m_matrix + 4 * 0);
        __m128 _a_row1 = mm_load_ps(a.m_matrix + 4 * 1);
        __m128 _a_row2 = mm_load_ps(a.m_matrix + 4 * 2);
        __m128 _a_row3 = mm_load_ps(a.m_matrix + 4 * 3);

        __m128 _b_row0 = mm_load_ps(b.m_matrix + 4 * 0);
        __m128 _b_row1 = mm_load_ps(b.m_matrix + 4 * 1);
        __m128 _b_row2 = mm_load_ps(b.m_matrix + 4 * 2);
        __m128 _b_row3 = mm_load_ps(b.m_matrix + 4 * 3);

        __m128 _dst;
        _dst = _mm_cmpeq_ps(_a_row0, _b_row0);
        _dst = _mm_and_ps(_dst, _mm_cmpeq_ps(_a_row1, _b_row1));
        _dst = _mm_and_ps(_dst, _mm_cmpeq_ps(_a_row2, _b_row2));
        _dst = _mm_and_ps(_dst, _mm_cmpeq_ps(_a_row3, _b_row3));

        __m64 _dsti = _mm_cvt_ps2pi(_dst);

        return (_dsti[0] & _dsti[1]) != 0;

    }
    
    bool operator!=(const Matrix4f& a, const Matrix4f& b)
    {
        return !(a == b);
    }
}