#include <GL/glew.h>
#include "renderer.hpp"
#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int Count) : m_Count(Count)
{
    GLErrCall(glGenBuffers(1, &m_RenderID));
    GLErrCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
    GLErrCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLErrCall(glDeleteBuffers(1, &m_RenderID));
}

void IndexBuffer::Bind() const
{
    GLErrCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
}

void IndexBuffer::UnBind() const
{
    GLErrCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
