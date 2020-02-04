#include "Test3D.hpp"
#include <GLFW/glfw3.h>
#include "./../src/renderer.hpp"
#include "./../src/Texture.hpp"
#include "./../dep/imgui/imgui.h"
#include "./../dep/glm/vec3.hpp"
#include "./../dep/glm/vec4.hpp"
#include "./../dep/glm/glm.hpp"
#include "./../dep/glm/gtc/type_ptr.hpp"
#include "./../dep/glm/gtc/matrix_transform.hpp"
#include <cstdlib>
#include <ctime>

namespace test
{

Test3D::Test3D() : m_proj(1.0f), m_camView(1.0f), m_modelT(1.0f)
{
    srand(time(0));
    std::vector<Vertex *> vertecies;

    for (size_t i = 0; i < 8; i++)
    {
        vertecies.push_back(new Vertex);
        vertecies[i]->pos = glm::vec3(0.0f, 0.0f, 0.0f);
        vertecies[i]->color = glm::vec4(((float)(rand() % 100)) / 100.0f, ((float)(rand() % 100)) / 100.0f, ((float)(rand() % 100)) / 100.0f, 1.0f);
    }

    vertecies[0]->pos = glm::vec3(-50.0f, -50.0f, 50.0f);
    vertecies[1]->pos = glm::vec3(50.0f, -50.0f, 50.0f);
    vertecies[2]->pos = glm::vec3(50.0f, 50.0f, 50.0f);
    vertecies[3]->pos = glm::vec3(-50.0f, 50.0f, 50.0f);
    vertecies[4]->pos = glm::vec3(-50.0f, -50.0f, -50.0f);
    vertecies[5]->pos = glm::vec3(50.0f, -50.0f, -50.0f);
    vertecies[6]->pos = glm::vec3(50.0f, 50.0f, -50.0f);
    vertecies[7]->pos = glm::vec3(-50.0f, 50.0f, -50.0f);

    /*   float verticesss[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        100.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        100.0f, 100.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 100.0f, 0.0f, 0.0f, 1.0f}; */

    unsigned int indecies[] = {
        0, 1, 2, 2, 3, 0, //onyuz
        1, 5, 6, 6, 2, 1, //sağyuz
        5, 4, 7, 7, 6, 5, //arkayuz
        4, 0, 3, 3, 7, 4, //solyuz
        3, 2, 6, 6, 7, 3, //ustyuz
        0, 1, 5, 5, 4, 0  //altyuz
    };

    m_va = std::make_unique<VertexArray>();
    m_vb = std::make_unique<VertexBuffer>(vertecies, vertecies.size() * 7 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(4);
    m_va->AddBuffer(*m_vb, layout);
    m_ib = std::make_unique<IndexBuffer>(indecies, 36);

    m_shader = std::make_unique<ShaderProgram>("./../shaders/VertexShader_3D.vert", "./../shaders/FragmentShader_3D.frag");

    GLErrCall(glEnable(GL_DEPTH_TEST));
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
    GLErrCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    renderer renderer;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

    m_proj = glm::perspective(glm::radians(90.0f), ((float)w) / ((float)h), 0.1f, 1000.0f);

    glm::vec3 camPos(m_camPX, m_camPY, m_camPZ);
    glm::vec3 camLookAt(0.0f, 0.0f, 0.0f);
    glm::vec3 camUp(0.0f, 1.0f, 0.0f);

    m_camView = glm::lookAt(camPos, camLookAt, camUp);

    Transform::TranslateXYZ(m_modelT, sin(glfwGetTime()) * 100, sin(glfwGetTime()) * 100, sin(glfwGetTime()) * 100);
    Transform::RotateXYZ(m_modelT, glfwGetTime() * 100, sin(glfwGetTime()) * 100, sin(glfwGetTime()) * 100);
    Transform::ScaleXYZ(m_modelT, sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime()));

    u_MVP = m_proj * m_camView * m_modelT;

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
    ImGui::SliderFloat("cameraPosZ", &m_camPZ, 1000.0f, -1000.0f);

    ImGui::SliderFloat("cameraRotX", &m_camRX, 0.0f, 1.0f);
    ImGui::SliderFloat("cameraRotY", &m_camRY, 0.0f, 1.0f);
    ImGui::SliderFloat("cameraRotZ", &m_camRZ, 0.0f, 360.0f);

    ImGui::SliderFloat("model1PosX", &m_modelPX, 0.0f, (float)w);
    ImGui::SliderFloat("model1PosY", &m_modelPY, 0.0f, (float)h);
    ImGui::SliderFloat("model1PosZ", &m_modelPZ, 100.0f, -100.0f);

    ImGui::SliderFloat("model1RotX", &m_modelRX, 0.0f, 360.0f);
    ImGui::SliderFloat("model1RotY", &m_modelRY, 0.0f, 360.0f);
    ImGui::SliderFloat("model1RotZ", &m_modelRZ, 0.0f, 360.0f);

    ImGui::SliderFloat("model1ScaleX", &m_modelSX, 0.0f, 1.0f);
    ImGui::SliderFloat("model1ScaleY", &m_modelSY, 0.0f, 1.0f);
    ImGui::SliderFloat("model1ScaleZ", &m_modelSZ, 0.0f, 1.0f);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // namespace test