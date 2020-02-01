#pragma once

#include "./../dep/glm/vec3.hpp"
#include "./../dep/glm/vec4.hpp"
#include "./../dep/glm/glm.hpp"

struct Vertex
{
    glm::vec3 pos;
    glm::vec4 color;
};

class VertexBuffer
{
private:
    unsigned int m_RendererID;

public:
    VertexBuffer(const void *data, unsigned int size);
    VertexBuffer(std::vector<Vertex *> data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};
