#include <GL/glew.h>
#include "renderer.hpp"
#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(std::vector<Vertex *> data, unsigned int size)
{
    int j = 0;

    float *dat = new float[data.size() * 7 * sizeof(float)];

    for (size_t i = 0; i < data.size(); i++)
    {
        dat[j] = data[i]->pos.x;
        dat[j + 1] = data[i]->pos.y;
        dat[j + 2] = data[i]->pos.z;
        dat[j + 3] = data[i]->color.r;
        dat[j + 4] = data[i]->color.g;
        dat[j + 5] = data[i]->color.b;
        dat[j + 6] = data[i]->color.a;
        j += 7;
    }

    GLErrCall(glGenBuffers(1, &m_RendererID));
    GLErrCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLErrCall(glBufferData(GL_ARRAY_BUFFER, size, (const void *)dat, GL_STATIC_DRAW));
}

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