#pragma once

#include "mxpch.hpp"

#include "math3D/Matrix4f.hpp"
#include "math3D/Matrix3f.hpp"
#include "math3D/Matrix2f.hpp"

#include "math3D/Vector4f.hpp"
#include "math3D/Vector3f.hpp"
#include "math3D/Vector2f.hpp"

#include "math3D/Quaternion.hpp"

namespace math3D
{
    template<typename Ostream>
    Ostream& operator<<(Ostream& stream, const Matrix4f& matrix)
    {
        std::stringstream ss;
        ss << "\n";
        
        matrix.print(ss);
        fmt::format_to(std::ostream_iterator<char>(stream), ss.str());


        return stream;
    }

    template<typename Ostream>
    Ostream& operator<<(Ostream& stream, const Matrix3f& matrix)
    {
        std::stringstream ss;
        ss << "\n";
        matrix.print(ss);
        fmt::format_to(std::ostream_iterator<char>(stream), ss.str());
        return stream;
    }

    template<typename Ostream>
    Ostream& operator<<(Ostream& stream, const Matrix2f& matrix)
    {
        std::stringstream ss;
        ss << "\n";
        matrix.print(ss);
        fmt::format_to(std::ostream_iterator<char>(stream), ss.str());
        return stream;
    }

    template<typename Ostream>
    Ostream& operator<<(Ostream& stream, const Vector4f& vector)
    {

        std::stringstream ss;
        vector.print(ss);
        fmt::format_to(std::ostream_iterator<char>(stream), ss.str());
        return stream;

    }

    template<typename Ostream>
    Ostream& operator<<(Ostream& stream, const Vector3f& vector)
    {
        std::stringstream ss;
        vector.print(ss);
        fmt::format_to(std::ostream_iterator<char>(stream), ss.str());
        return stream;

    }

    template<typename Ostream>
    Ostream& operator<<(Ostream& stream, const Vector2f& vector)
    {
        std::stringstream ss;
        vector.print(ss);
        fmt::format_to(std::ostream_iterator<char>(stream), ss.str());
        return stream;

    }

    template<typename Ostream>
    Ostream& operator<<(Ostream& stream, const Quaternion& q)
    {
        std::stringstream ss;
        q.print(ss);
        fmt::format_to(std::ostream_iterator<char>(stream), ss.str());
        return stream;
    }
}