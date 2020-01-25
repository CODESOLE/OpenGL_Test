#include <GL/glew.h>
#include "renderer.hpp"
#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    GLErrCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLErrCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
    GLErrCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
    GLErrCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const auto &elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        GLErrCall(glEnableVertexAttribArray(i));
        GLErrCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), reinterpret_cast<const void *>(offset)));
        offset = element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}