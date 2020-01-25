#include "renderer.hpp"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
    {
    };
}

bool GLLogCall(const char *funcName, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "-------------ERROR-----------------" << std::endl;
        std::cout << "[OpenGL Error] (0X0" << std::hex << error << std::dec << ") "
                  << "FUNC_NAME: " << funcName << "  "
                  << "FILE_NAME: " << file << "  LINE: " << line << std::endl
                  << std::endl;
        return false;
    }
    return true;
}

void renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const ShaderProgram &shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLErrCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void renderer::Clear() const
{
    GLErrCall(glClear(GL_COLOR_BUFFER_BIT));
}