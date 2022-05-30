#include "mxpch.hpp"
#include "OpenGLShader.hpp"

#include <fstream>

static GLenum GLShaderType(mx::ShaderType shaderType)
{
    GLenum type = 0;
    switch (shaderType)
    {
        case mx::ShaderType::Vertex: type = GL_VERTEX_SHADER; break;
        case mx::ShaderType::Fragment: type = GL_FRAGMENT_SHADER; break;
        default: MX_CORE_ASSERT(false, "shader type unknown {}", (int)shaderType);
    }
    return type;
}

mx::OpenGLShader::OpenGLShader(const std::array<ShaderSource, NB_SHADER_TYPES>& shaders)
{
    compile(shaders);
}


mx::OpenGLShader::OpenGLShader(const std::string& filepath)
{
    std::string source = readFile(filepath);
    auto shaders = preProcess(source);
    compile(shaders);
    
    auto slashPos = filepath.find_last_of("/\\");
    auto extPos = filepath.find_last_of(".");
    m_name = filepath.substr(slashPos + 1, extPos - slashPos - 1);
}

void mx::OpenGLShader::bind()
{
    glUseProgram(m_rendererID);
}

void mx::OpenGLShader::setUniform(const std::string& name, const float& value)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform1f(loc, value);
}

void mx::OpenGLShader::setUniform(const std::string& name, const math3D::Vector2f& value)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform2f(loc, value.x, value.y);
}

void mx::OpenGLShader::setUniform(const std::string& name, const math3D::Vector3f& value)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform3f(loc, value.x, value.y, value.z);
}

void mx::OpenGLShader::setUniform(const std::string& name, const math3D::Vector4f& value)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform4f(loc, value.x, value.y, value.z, value.w);
}

void mx::OpenGLShader::setUniform(const std::string& name, float* value, uint32_t count)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform1fv(loc, count, value);
}

void mx::OpenGLShader::setUniform(const std::string& name, math3D::Vector2f* value, uint32_t count)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform2fv(loc, count, (GLfloat*)value);
}

void mx::OpenGLShader::setUniform(const std::string& name, math3D::Vector3f* value, uint32_t count)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform3fv(loc, count, (GLfloat*)value);
}

void mx::OpenGLShader::setUniform(const std::string& name, math3D::Vector4f* value, uint32_t count)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform4fv(loc, count, (GLfloat*)value);
}

void mx::OpenGLShader::setUniform(const std::string& name, const math3D::Matrix4f& value)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_TRUE, (GLfloat*)&value);
}

void mx::OpenGLShader::setUniform(const std::string& name, const math3D::Matrix3f& value)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniformMatrix3fv(loc, 1, GL_TRUE, (GLfloat*)&value);
}

void mx::OpenGLShader::setUniform(const std::string& name, math3D::Matrix4f* value, uint32_t count)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniformMatrix4fv(loc, count, GL_TRUE, (GLfloat*)&value);
}

void mx::OpenGLShader::setUniform(const std::string& name, math3D::Matrix3f* value, uint32_t count)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniformMatrix3fv(loc, count, GL_TRUE, (GLfloat*)&value);
}

void mx::OpenGLShader::setUniform(const std::string& name, const int& value)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform1i(loc, value);
}

void mx::OpenGLShader::setUniform(const std::string& name, int* value, uint32_t count)
{
    uint32_t loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform1iv(loc, count, (GLint*)&value);
}

void mx::OpenGLShader::setUniform(const std::string& name, const Color& color)
{
    RendererID loc = glGetUniformLocation(m_rendererID, name.c_str());
    glUniform4f(loc, color.r, color.g, color.b, color.a);
}

bool mx::OpenGLShader::compileShader(const std::string& shaderSource, GLenum shaderType, GLuint& shaderID, std::vector<GLchar>& infoLog)
{
    shaderID = glCreateShader(shaderType);

    const GLchar *source = (const GLchar *)shaderSource.c_str();
    glShaderSource(shaderID, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(shaderID);

    GLint isCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
        infoLog.clear();
        infoLog.resize(maxLength);
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);
        
        return false;
    }

    return true;
}

std::string mx::OpenGLShader::readFile(const std::string& filepath)
{
    std::ifstream in(filepath);
    std::string source;
    if (in)
    {
        in.seekg(0, std::ios::end);
        source.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(source.data(), source.size());
    }
    else
        MX_CORE_ERROR("Cannot open shader source file : {}", filepath);

    return source;
}

std::array<mx::ShaderSource, NB_SHADER_TYPES> mx::OpenGLShader::preProcess(const std::string& source)
{
    std::array<mx::ShaderSource, NB_SHADER_TYPES> shaders;
    std::string keyWord = "#type";
    size_t pos = source.find("#type");

    int i = 0;
    while (pos != std::string::npos)
    {
        MX_CORE_ASSERT(i < NB_SHADER_TYPES, "Too much shaders in file");
        size_t keyWordLastPos = pos + keyWord.size();

        size_t newlinePos = source.find("\n", keyWordLastPos);
        std::string type = source.substr(keyWordLastPos, newlinePos - keyWordLastPos);
        type.erase(std::remove_if(type.begin(), type.end(), ::isspace), type.end());


        size_t keyWordPos = source.find("#type", newlinePos + 1);
        std::string shaderSource;
        shaderSource = source.substr(newlinePos, 
        keyWordPos == std::string::npos ? keyWordPos : keyWordPos - newlinePos);

        shaders[i++] = {shaderSource, getShaderType(type)};
        pos = keyWordPos;

    }

    return shaders;
}

void mx::OpenGLShader::compile(const std::array<ShaderSource, NB_SHADER_TYPES>& shaders)
{
    std::array<GLuint, NB_SHADER_TYPES> shadersIDs;
    int i = 0;
    std::vector<GLchar> infoLog;
    bool success = true;
    for (auto& shaderSource : shaders)
    {
        if (!compileShader(shaderSource.Source, GLShaderType(shaderSource.Type), shadersIDs[i], infoLog))
        {
            success = false;
            break;
        }
        i++;
    }
    if (!success)
    {
        MX_CORE_ERROR("Compiling {} shader failed", shaderTypes[(int)shaders[i].Type]);
        MX_CORE_ERROR(reinterpret_cast<const char*>(infoLog.data()));
        while (--i >= 0)
            glDeleteShader(shadersIDs[i]);

        return;
    }

    m_rendererID = glCreateProgram();

    // Attach our shaders to our program
    for (GLuint shaderID : shadersIDs)
        glAttachShader(m_rendererID, shaderID);

    // Link our program
    glLinkProgram(m_rendererID);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(m_rendererID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, &infoLog[0]);

        // Don't leak shaders either.
        for (GLuint shaderID : shadersIDs)
            glDeleteShader(shaderID);

        MX_CORE_ERROR("Program linking failed");
        MX_CORE_ASSERT(false, reinterpret_cast<const char*>(infoLog.data()));

    }

    // Always detach shaders after a successful link.
    for (GLuint shaderID : shadersIDs)
        glDetachShader(m_rendererID, shaderID);
}