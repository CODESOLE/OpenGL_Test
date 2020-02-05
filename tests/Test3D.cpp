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

Test3D::Test3D() : m_proj(1.0f), m_camView(1.0f), m_modelT(1.0f),
                   m_camPos(0.0f, 0.0f, 300.0f), m_camLookAt(0.f, 0.f, -1.f), m_camUp(0.f, 1.f, 0.f),
                   lastX(((float)w) / 2.f), lastY(((float)h) / 2.f), firstMouse(true), yaw(0.0), pitch(0.0)
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

void Test3D::OnUpdate(float deltaTime, GLFWwindow *window, double xpos, double ypos)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    float cameraSpeed = 1000.f * deltaTime; // adjust accordingly

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_camPos += cameraSpeed * m_camLookAt;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_camPos -= cameraSpeed * m_camLookAt;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_camPos -= glm::normalize(glm::cross(m_camLookAt, m_camUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_camPos += glm::normalize(glm::cross(m_camLookAt, m_camUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        m_camPos += m_camUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        m_camPos -= m_camUp * cameraSpeed;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_camLookAt = glm::normalize(direction);
}

void Test3D::OnRender()
{
    GLErrCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLErrCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    renderer renderer;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

    m_proj = glm::perspective(glm::radians(90.0f), ((float)w) / ((float)h), 0.1f, 1000.0f);

    m_camView = glm::lookAt(m_camPos, m_camPos + m_camLookAt, m_camUp);

    //Transform::TranslateXYZ(m_modelT, sin(glfwGetTime()) * 100, sin(glfwGetTime()) * 100, sin(glfwGetTime()) * 100);
    Transform::TranslateXYZ(m_modelT, 10.f, 10.f, 0.f);
    Transform::RotateXYZ(m_modelT, glfwGetTime() * 100, sin(glfwGetTime()) * 100, sin(glfwGetTime()) * 100);
    //Transform::ScaleXYZ(m_modelT, sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime()));

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