#pragma once

#include <./GL/glew.h>
#include <signal.h>
#define _DEBUG
void GLClearError();
bool GLLogCall(const char *funcName, const char *file, int line);
#define ASSERT(x) \
    if (!(x))     \
        raise(SIGTRAP);

#ifdef _DEBUG
#define GLErrCall(x) \
    GLClearError();  \
    x;               \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLErrCall(x) x
#endif

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "ShaderProgram.hpp"

class ShaderProgram;
class VertexArray;

void GLClearError();

bool GLLogCall(const char *funcName, const char *file, int line);

class renderer
{
private:
    /* data */
public:
    void Draw(const VertexArray &va, const IndexBuffer &ib, const ShaderProgram &shader) const;
    void Clear() const;
};
