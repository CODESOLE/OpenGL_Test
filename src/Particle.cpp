#include "Particle.hpp"

Particle::Particle(const float &posx, const float &posy) : m_PosX(posx), m_PosY(posy)
{

    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rotDirect(0, 1);
    m_rotdirect = rotDirect(rng);
    std::uniform_real_distribution<double> rot(0.0, 360.0);
    m_rotation = (float)rot(rng);
    std::uniform_real_distribution<double> l(10.0, 50.0);
    m_length = (float)l(rng);
    std::uniform_real_distribution<double> col(0.0, 1.0);
    for (int i = 0; i < 3; i++)
        m_color[i] = (float)col(rng);
    m_color.a = 1.f;

    for (size_t i = 0; i < 4; i++)
    {
        vertexx.push_back(new Vertex);
        vertexx[i]->color = m_color;
    }
    vertexx[0]->pos = glm::vec3(m_PosX - (m_length / 2.f), m_PosY - (m_length / 2.f), 0.f);
    vertexx[1]->pos = glm::vec3(m_PosX + (m_length / 2.f), m_PosY - (m_length / 2.f), 0.f);
    vertexx[2]->pos = glm::vec3(m_PosX + (m_length / 2.f), m_PosY + (m_length / 2.f), 0.f);
    vertexx[3]->pos = glm::vec3(m_PosX - (m_length / 2.f), m_PosY + (m_length / 2.f), 0.f);

    unsigned int indecies[] = {0, 1, 2, 2, 3, 0};

    m_va = std::make_unique<VertexArray>();
    m_vb = std::make_unique<VertexBuffer>(vertexx, sizeof(vertexx));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(4);
    m_va->AddBuffer(*m_vb, layout);
    m_ib = std::make_unique<IndexBuffer>(indecies, 6);

    m_shader = std::make_unique<ShaderProgram>("./../shaders/VertexShader_3D.vert", "./../shaders/FragmentShader_3D.frag");
}

void Particle::addRot(const float &val)
{
    if (m_rotdirect == 0) //anti-cloclwise
        m_rotation -= val;
    else if (m_rotation == 1) //cloclwise
        m_rotation += val;
}

float Particle::getRot() const { return m_rotation; }

Particle::~Particle()
{
}