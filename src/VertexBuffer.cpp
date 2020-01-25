#include <GL/glew.h>
#include "renderer.hpp"
#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    GLErrCall(glGenBuffers(1, &m_RendererID));
    GLErrCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLErrCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLErrCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLErrCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind() const
{
    GLErrCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}