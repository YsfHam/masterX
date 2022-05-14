#include "mxpch.hpp"
#include "OpenGLShader.hpp"

mx::OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragSrc)
{
    std::vector<GLchar> infoLog;

    RendererID vertexShader;
    if (!compileShader(vertexSrc, GL_VERTEX_SHADER, vertexShader, infoLog))
    {
        glDeleteShader(vertexShader);
        MX_CORE_ERROR("Vertex shader compiling failed");
        MX_CORE_ASSERT(false, reinterpret_cast<const char*>(infoLog.data()));
    }

    RendererID fragmentShader;
    if (!compileShader(fragSrc, GL_FRAGMENT_SHADER, fragmentShader, infoLog))
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        MX_CORE_ERROR("fragment shader compiling failed");
        MX_CORE_ASSERT(false, reinterpret_cast<const char*>(infoLog.data()));
    }

    m_shaderID = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(m_shaderID, vertexShader);
    glAttachShader(m_shaderID, fragmentShader);

    // Link our program
    glLinkProgram(m_shaderID);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(m_shaderID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_shaderID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_shaderID, maxLength, &maxLength, &infoLog[0]);

        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        MX_CORE_ERROR("Program linking failed");
        MX_CORE_ASSERT(false, reinterpret_cast<const char*>(infoLog.data()));

    }

    // Always detach shaders after a successful link.
    glDetachShader(m_shaderID, vertexShader);
    glDetachShader(m_shaderID, fragmentShader);

}

void mx::OpenGLShader::bind()
{
    glUseProgram(m_shaderID);
}

bool mx::OpenGLShader::compileShader(const std::string& shaderSource, GLenum shaderType, RendererID& shaderID, std::vector<GLchar>& infoLog)
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