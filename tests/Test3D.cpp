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
                   lastX(((float)w) / 2.f), lastY(((float)h) / 2.f), firstMouse(true), yaw(0.0), pitch(0.0), fov(45.0),
                   camera(glm::vec3(0.f, 0.f, 300.f))
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

void Test3D::OnUpdate(float deltaTime, GLFWwindow *window, double xpos, double ypos, double scroll_xoffset, double scroll_yoffset)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //---------keyboard event
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    float cameraSpeed = 500.f * deltaTime; // adjust accordingly

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, cameraSpeed);

    //---------mouse scroll zoom
    camera.ProcessMouseScroll(scroll_yoffset);

    //---------mouse looka round
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

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void Test3D::OnRender()
{
    GLErrCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLErrCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    renderer renderer;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

    m_proj = glm::perspective(glm::radians(camera.Zoom), ((float)w) / ((float)h), 0.1f, 10000.0f);

    //Transform::TranslateXYZ(m_modelT, sin(glfwGetTime()) * 100, sin(glfwGetTime()) * 100, sin(glfwGetTime()) * 100);
    Transform::TranslateXYZ(m_modelT, 0.f, 0.f, 300.f);
    Transform::RotateXYZ(m_modelT, glfwGetTime() * 100, sin(glfwGetTime()) * 100, sin(glfwGetTime()) * 100);
    //Transform::ScaleXYZ(m_modelT, sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime()));

    u_MVP = m_proj * camera.GetViewMatrix() * m_modelT;

    m_shader->Bind();
    m_shader->setUniformMat4f("u_MVP", u_MVP);

    m_va->Bind();
    m_ib->Bind();

    renderer.Draw(*m_va, *m_ib, *m_shader);
}

void Test3D::OnImGuiRender()
{
    ImGui::Text("Use W, A, S, D, Q, E to fly around and use mouse to control the camera angle!");
    ImGui::Text("Press ESC to Exit!");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // namespace test