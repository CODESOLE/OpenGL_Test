#pragma once

#include "./../dep/glm/glm.hpp"
#include "./../dep/glm/gtc/matrix_transform.hpp"
#include "./../dep/glm/vec4.hpp"
#include "./../src/VertexArray.hpp"
#include "./../src/VertexBuffer.hpp"
#include "./../src/IndexBuffer.hpp"
#include <random>
#include <memory>

class Particle
{
public:
    std::unique_ptr<VertexArray> m_va;
    std::unique_ptr<IndexBuffer> m_ib;
    std::unique_ptr<ShaderProgram> m_shader;

private:
    std::vector<Vertex *> vertexx;
    float m_PosX, m_PosY, m_length, m_lifeTime = 3.f, m_rotation;
    int m_rotdirect;
    glm::vec4 m_color;
    std::random_device dev;
    std::unique_ptr<VertexBuffer> m_vb;

public:
    Particle(const float &posx, const float &posy);
    void addRot(const float &);
    float getRot() const;
    ~Particle();
};
