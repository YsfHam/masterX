#pragma once

#include "mxpch.hpp"
#include "utils/types.hpp"
#include "core/Assert.hpp"

namespace mx
{

    struct ShaderDataType
    {
        uint32_t Size;
        enum Type
        {
            Float, Vec2, Vec3, Vec4, Mat3, Mat4,
            Int, IVec2, IVec3, IVec4,
            Bool
        } DataType;

        ShaderDataType(Type dataType)
            : DataType(dataType)
        {
            switch (dataType)
            {
                case Float:  Size = sizeof(float);         break;
                case Vec2:   Size = sizeof(float) * 2;     break;
                case Vec3:   Size = sizeof(float) * 3;     break;
                case Vec4:   Size = sizeof(float) * 4;     break;
                case Mat3:   Size = sizeof(float) * 3 * 3; break;
                case Mat4:   Size = sizeof(float) * 4 * 4; break;

                case Int:     Size = sizeof(int);         break;
                case IVec2:   Size = sizeof(int) * 2;     break;
                case IVec3:   Size = sizeof(int) * 3;     break;
                case IVec4:   Size = sizeof(int) * 4;     break;

                case Bool: Size = sizeof(bool); break;

                default: MX_CORE_ASSERT(false, "Unknown data type");
            }
        }

        uint32_t getComponentCount() const
        {
            switch (DataType)
            {
                case Float: return 1;
                case Vec2:  return 2; 
                case Vec3:  return 3; 
                case Vec4:  return 4; 
                case Mat3:  return 3 * 3; 
                case Mat4:  return 4 * 4; 

                case Int:   return 1;  
                case IVec2: return 2;  
                case IVec3: return 3;  
                case IVec4: return 4;  

                case Bool: return 1;
            }

            MX_CORE_ASSERT(false, "Cannot get the number of components");
            return 0;

        }
    };

    struct BufferElement
    {
        std::string Name;
        ShaderDataType DataType;

        size_t Offset;
        bool Normalized;

        BufferElement() = default;
        BufferElement(ShaderDataType dataType, const std::string& name, bool normalized = false)
            : Name(name), DataType(dataType), Offset(0), Normalized(normalized)
        {}

    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;

        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_elements(elements), m_stride(0)
        {
            uint32_t offset = 0;
            for (auto& element : m_elements)
            {
                element.Offset = offset;
                offset = m_stride += element.DataType.Size;
            }
        }

        bool isEmpty() const { return m_elements.empty(); }

        uint32_t getStride() const { return m_stride; }

        std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

    private:
        std::vector<BufferElement> m_elements;

        uint32_t m_stride;
    };

    class VertexBuffer
    {
    public:
        static Ref<VertexBuffer> Create(void *vertices, uint32_t size);
        static Ref<VertexBuffer> Create(uint32_t size);

        virtual ~VertexBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
        
        void setLayout(BufferLayout layout) { m_layout = layout; }
        const BufferLayout& getLayout() const { return m_layout; }

    private:
        BufferLayout m_layout;

    };

    class IndexBuffer
    {
    public:
        static Ref<IndexBuffer> Create(uint32_t *indices, uint32_t count);
        static Ref<IndexBuffer> Create(uint32_t count);

        virtual ~IndexBuffer() =default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual uint32_t getCount() const = 0;
    };
}