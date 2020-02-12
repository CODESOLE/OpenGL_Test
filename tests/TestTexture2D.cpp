#include "TestTexture2D.hpp"
#include <GLFW/glfw3.h>
#include "./../src/renderer.hpp"
#include "./../src/Texture.hpp"
#include "./../dep/imgui/imgui.h"
#include "./../dep/glm/vec3.hpp"
#include "./../dep/glm/vec4.hpp"
#include "./../dep/glm/glm.hpp"
#include "./../dep/glm/gtc/matrix_transform.hpp"
#include <chrono>

namespace test
{

TestTexture2D::TestTexture2D() : m_trans(1.0f)
{

    float verticesss[] = {
        -50.0f, -50.0f, 0.0f, 0.0f, 0.0f,
        50.0f, -50.0f, 0.0f, 1.0f, 0.0f,
        50.0f, 50.0f, 0.0f, 1.0f, 1.0f,
        -50.0f, 50.0f, 0.0f, 0.0f, 1.0f};

    unsigned int indecies[] = {0, 1, 2, 2, 3, 0};

    m_va = std::make_unique<VertexArray>();
    m_vb = std::make_unique<VertexBuffer>(verticesss, sizeof(verticesss));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_va->AddBuffer(*m_vb, layout);
    m_ib = std::make_unique<IndexBuffer>(indecies, 6);

    m_shader = std::make_unique<ShaderProgram>("./../shaders/VertexShader.vert", "./../shaders/FragmentShader.frag");

    m_texture = std::make_unique<Texture>("./../res/arduino.png");

    m_texture2 = std::make_unique<Texture>("./../res/mikael-gustafsson-amongtrees-2-8.jpg");
}

TestTexture2D::~TestTexture2D()
{
}

void TestTexture2D::OnUpdate(float deltaTime, GLFWwindow *window, double xpos, double ypos, double xoffset, double yoffset)
{
}

void TestTexture2D::OnRender()
{
    double current = glfwGetTime();
    GLErrCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLErrCall(glClear(GL_COLOR_BUFFER_BIT));
    renderer renderer;
    m_texture->Bind();
    glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);
    glm::mat4 m_proj(1.0f);
    m_proj = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f);
    glm::mat4 m_view(1.0f);

    m_trans = glm::translate(glm::mat4(1.f), glm::vec3(500.5f, 500.5f, 0.0f));
    m_trans = glm::rotate(m_trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    m_trans = glm::scale(m_trans, glm::vec3(m_x, m_y, 1.0f));

    glm::mat4 u_MVP = m_proj * m_view * m_trans;

    m_shader->Bind();
    m_shader->setUniformMat4f("u_MVP", u_MVP);

    m_va->Bind();
    m_ib->Bind();

    renderer.Draw(*m_va, *m_ib, *m_shader);

    m_texture2->Bind();
    m_model2 = glm::translate(glm::mat4(1), glm::vec3(m_a, m_b, 0.0f));
    u_MVP = m_proj * m_view * m_model2;
    m_shader->setUniformMat4f("u_MVP", u_MVP);

    renderer.Draw(*m_va, *m_ib, *m_shader);
}

void TestTexture2D::OnImGuiRender()
{
    ImGui::SliderFloat("model1ScaleX", &m_x, 0.0f, 1.0f);
    ImGui::SliderFloat("model1ScaleY", &m_y, 0.0f, 1.0f);

    ImGui::SliderFloat("model2X", &m_a, 0.0f, (float)w);
    ImGui::SliderFloat("model2Y", &m_b, 0.0f, (float)h);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // namespace test