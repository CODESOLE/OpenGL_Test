#include "ShaderProgram.hpp"

GLuint ShaderProgram::checkandGetUniformLocation(const char *varname) const
{
    if (m_UniformVar.find(varname) != m_UniformVar.end())
    {
        return m_UniformVar[varname];
    }
    else
    {
        GLErrCall(int location = glGetUniformLocation(m_ShaderProgramId, varname));
        if (location == -1)
            std::cout << "Warning: Uniform " << varname << "doesn't exist!" << std::endl;
        m_UniformVar[varname] = location;
        return location;
    }
}

void ShaderProgram::setUniformMat4f(const char *varName, const glm::mat4 &proj)
{
    GLErrCall(glUniformMatrix4fv(checkandGetUniformLocation(varName), 1, GL_FALSE, glm::value_ptr(proj)));
}

void ShaderProgram::setUniformFloat4(const char *varname, glm::vec4 _value)
{
    GLErrCall(glUniform4f(checkandGetUniformLocation(varname), _value.r, _value.g, _value.b, _value.a));
}

void ShaderProgram::setUniformInt1(const char *varName, int val)
{
    GLErrCall(glUniform1i(checkandGetUniformLocation(varName), val));
}

ShaderProgram::ShaderProgram(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{
    std::string line;

    std::ifstream streamVertex(vertexShaderFilePath);
    std::string dataVertex;

    if (streamVertex.is_open())
    {
        while (getline(streamVertex, line))
            dataVertex.append(line + '\n');
        streamVertex.close();
        line.empty();
    }

    std::ifstream streamFragment(fragmentShaderFilePath);
    std::string dataFragment;

    if (streamFragment.is_open())
    {
        while (getline(streamFragment, line))
            dataFragment.append(line + '\n');
        streamFragment.close();
        line.empty();
    }

    GLErrCall(m_ShaderProgramId = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, dataVertex);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, dataFragment);

    GLErrCall(glAttachShader(m_ShaderProgramId, vs));
    GLErrCall(glAttachShader(m_ShaderProgramId, fs));
    GLErrCall(glLinkProgram(m_ShaderProgramId));
    GLErrCall(glValidateProgram(m_ShaderProgramId));

    int isLinked;
    char log[512];
    GLErrCall(glGetProgramiv(m_ShaderProgramId, GL_LINK_STATUS, &isLinked));
    if (!isLinked)
    {
        GLErrCall(glGetProgramInfoLog(m_ShaderProgramId, 512, 0, log));
        std::cout << "Program Linking Error: " << log << std::endl;
    }

    GLErrCall(glDeleteShader(vs));
    GLErrCall(glDeleteShader(fs));
}

void ShaderProgram::Bind() const
{
    GLErrCall(glUseProgram(m_ShaderProgramId));
}

void ShaderProgram::UnBind() const
{
    GLErrCall(glUseProgram(0));
}

unsigned int ShaderProgram::CompileShader(unsigned int type, const std::string &source)
{
    GLErrCall(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GLErrCall(glShaderSource(id, 1, &src, nullptr));
    GLErrCall(glCompileShader(id));

    int result;
    GLErrCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int lenght;
        GLErrCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
        char *message = (char *)alloca(lenght * sizeof(char));
        GLErrCall(glGetShaderInfoLog(id, lenght, &lenght, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << std::endl;
        std::cout << message << std::endl;
        GLErrCall(glDeleteShader(id));

        return 0;
    }

    return id;
}

ShaderProgram::~ShaderProgram()
{
    GLErrCall(glDeleteProgram(m_ShaderProgramId));
}