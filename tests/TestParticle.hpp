#pragma once

#include "Test.hpp"
#include "./../dep/glm/vec4.hpp"
#include "./../dep/glm/gtc/matrix_transform.hpp"
#include "./../dep/glm/gtc/type_ptr.hpp"
#include "./../src/renderer.hpp"
#include "./../src/VertexArray.hpp"
#include "./../src/Particle.hpp"
#include "./../src/VertexBuffer.hpp"
#include "./../src/IndexBuffer.hpp"

#include <memory>

namespace test
{
class TestParticle : public Test
{
private:
    std::vector<Particle *> particleContainer;

    glm::mat4 m_proj, m_view, m_model;
    int w, h;

public:
    TestParticle();
    ~TestParticle();

    void OnUpdate(float deltaTime, GLFWwindow *window, double xpos, double ypos, double xoffset, double yoffset) override;
    void OnRender() override;
    void OnImGuiRender() override;
};

} // namespace test