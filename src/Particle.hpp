#pragma once

#include "./../dep/glm/vec4.hpp"
#include "./../dep/glm/gtc/matrix_transform.hpp"
#include "./../dep/glm/gtc/type_ptr.hpp"
#include "renderer.hpp"

class Particle
{
private:
    float m_mousePosX, m_mousePosY, m_length, m_lifeTime, m_rotation;
    glm::vec4 m_color;

public:
    Particle(/* args */);
    ~Particle();
};
