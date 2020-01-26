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
    m_view = glm::translate(glm::mat4(1), glm::vec3(m_f, 0.0f, 0.0f));
    glm::mat4 u_MVP = m_proj * m_view;
    m_shader->Bind();
    m_shader->setUniformMat4f("u_MVP", u_MVP);

    //sp1.setUniformFloat4("u_Color", color);
    m_va->Bind();
    m_ib->Bind();
    renderer.Draw(*m_va, *m_ib, *m_shader);

    m_view2 = glm::translate(glm::mat4(1), glm::vec3(m_f2, 100.0f, 0.0f));
    u_MVP = m_proj * m_view2;
    m_shader->setUniformMat4f("u_MVP", u_MVP);

    renderer.Draw(*m_va, *m_ib, *m_shader);
}

void TestTexture2D::OnImGuiRender()
{
    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("float", &m_f, 0.0f, (float)w - 100.0f);
    ImGui::SliderFloat("float2", &m_f2, 0.0f, (float)w - 100.0f);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // namespace test