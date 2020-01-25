#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include "renderer.hpp"
#include <map>
#include "./../dep/glm/vec4.hpp"
#include "./../dep/glm/gtc/matrix_transform.hpp"

class ShaderProgram
{
private:
    unsigned int m_ShaderProgramId;
    std::map<const char *, int> m_UniformVar;

    unsigned int CompileShader(unsigned int, const std::string &);
    int getUniformLocation(const char *);

public:
    ShaderProgram(const std::string &, const std::string &);
    ~ShaderProgram();
    void Bind() const;
    void UnBind() const;
    void setUniformFloat4(const char *, glm::vec4);
    void setUniformInt1(const char *, int);
    void setUniformMat4f(const char *, const glm::mat4 &);
};
