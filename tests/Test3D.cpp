#include "Test3D.hpp"
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

Test3D::Test3D()
{

    float verticesss[] = {
        0.0f, 100.0f, 0.0f, 0.0f, 0.0f,
        100.0f, 100.0f, 0.0f, 1.0f, 0.0f,
        100.0f, 200.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 200.0f, 0.0f, 0.0f, 1.0f};

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
}

Test3D::~Test3D()
{
}

void Test3D::OnUpdate(float deltaTime)
{
}

void Test3D::OnRender()
{
    GLErrCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLErrCall(glClear(GL_COLOR_BUFFER_BIT));
    renderer renderer;
    m_texture->Bind();
    glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

    m_proj = glm::perspective(glm::radians(90.0f), ((float)w) / ((float)h), 1.0f, 100.0f);

    glm::vec3 camPos(m_camPX, m_camPY, m_camPZ);
    glm::vec3 camLookAt(m_camRX, m_camRY, m_camRZ);
    glm::vec3 camUp(0.0f, 1.0f, 0.0f);

    glm::mat4 camView = glm::lookAt(camPos, camLookAt, camUp);

    m_modelT = glm::translate(glm::mat4(1), glm::vec3(m_modelPX, m_modelPY, m_modelPZ));
    m_modelR = glm::rotate(glm::mat4(1), glm::radians(0.0f), glm::vec3(m_modelRX, m_modelRY, m_modelRZ));
    m_modelS = glm::scale(glm::mat4(1), glm::vec3(m_modelSX, m_modelSY, m_modelSZ));

    glm::mat4 m_model1 = m_modelT * m_modelR * m_modelS;

    glm::mat4 u_MVP = m_proj * m_view * m_model1;

    m_shader->Bind();
    m_shader->setUniformMat4f("u_MVP", u_MVP);

    m_va->Bind();
    m_ib->Bind();

    renderer.Draw(*m_va, *m_ib, *m_shader);
}

void Test3D::OnImGuiRender()
{
    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("cameraPosX", &m_camPX, 0.0f, (float)w);
    ImGui::SliderFloat("cameraPosY", &m_camPY, 0.0f, (float)h);
    ImGui::SliderFloat("cameraPosZ", &m_camPZ, 100.0f, -100.0f);

    ImGui::SliderFloat("cameraRotX", &m_camRX, 0.0f, 360.0f);
    ImGui::SliderFloat("cameraRotY", &m_camRY, 0.0f, 360.0f);
    ImGui::SliderFloat("cameraRotZ", &m_camRZ, 0.0f, 360.0f);

    ImGui::SliderFloat("model1PosX", &m_modelPX, 0.0f, (float)w);
    ImGui::SliderFloat("model1PosY", &m_modelPY, 0.0f, (float)h);
    ImGui::SliderFloat("model1PosZ", &m_modelPZ, 100.0f, -100.0f);

    ImGui::SliderFloat("model1RotX", &m_modelRX, 0.0f, 360.0f);
    ImGui::SliderFloat("model1RotY", &m_modelRY, 0.0f, 360.0f);
    ImGui::SliderFloat("model1RotZ", &m_modelRZ, 0.0f, 360.0f);

    ImGui::SliderFloat("model1ScaleX", &m_modelSX, 0.0f, (float)w);
    ImGui::SliderFloat("model1ScaleY", &m_modelSY, 0.0f, (float)h);
    ImGui::SliderFloat("model1ScaleZ", &m_modelSZ, 0.0f, (float)h);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // namespace test