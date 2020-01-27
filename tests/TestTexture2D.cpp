#include "TestTexture2D.hpp"
#include <GLFW/glfw3.h>
#include "./../src/renderer.hpp"
#include "./../src/Texture.hpp"
#include "./../dep/imgui/imgui.h"
#include "./../dep/glm/vec3.hpp"
#include "./../dep/glm/vec4.hpp"
#include "./../dep/glm/glm.hpp"
#include "./../dep/glm/gtc/matrix_transform.hpp"

namespace test
{

TestTexture2D::TestTexture2D()
{

    float verticesss[] = {
        0.0f, 100.0f, 0.0f, 0.0f,
        100.0f, 100.0f, 1.0f, 0.0f,
        100.0f, 200.0f, 1.0f, 1.0f,
        0.0f, 200.0f, 0.0f, 1.0f};

    unsigned int indecies[] = {0, 1, 2, 2, 3, 0};

    m_va = std::make_unique<VertexArray>();
    m_vb = std::make_unique<VertexBuffer>(verticesss, sizeof(verticesss));

    VertexBufferLayout layout;
    layout.Push<float>(2);
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

void TestTexture2D::OnUpdate(float deltaTime)
{
}

void TestTexture2D::OnRender()
{
    GLErrCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLErrCall(glClear(GL_COLOR_BUFFER_BIT));
    renderer renderer;
    m_texture->Bind();
    glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

    m_proj = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f);
    m_view = glm::rotate(glm::mat4(1), glm::radians(m_rot), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::translate(glm::mat4(1), glm::vec3(m_f, m_f2, 0.0f));
    m_model1 = glm::translate(glm::mat4(1), glm::vec3(m_x, m_y, 0.0f));
    glm::mat4 u_MVP = m_proj * m_view * m_model1;
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
    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("cameraX", &m_f, 0.0f, (float)w);
    ImGui::SliderFloat("cameraY", &m_f2, 0.0f, (float)h);
    ImGui::SliderFloat("cameraRot", &m_rot, 0.0f, 360.0f);

    ImGui::SliderFloat("model1X", &m_x, 0.0f, (float)w);
    ImGui::SliderFloat("model1Y", &m_y, 0.0f, (float)h);

    ImGui::SliderFloat("model2X", &m_a, 0.0f, (float)w);
    ImGui::SliderFloat("model2Y", &m_b, 0.0f, (float)h);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // namespace test