#include "TestParticle.hpp"
#include <GLFW/glfw3.h>
#include "./../dep/imgui/imgui.h"
namespace test
{

TestParticle::TestParticle() : m_proj(1.0f), m_view(1.0f), m_model(1.0f)
{
}

TestParticle::~TestParticle()
{
}

void TestParticle::OnUpdate(float deltaTime, GLFWwindow *window, double xpos, double ypos, double xoffset, double yoffset)
{
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        //std::cout << xpos << "   " << ypos << '\n';
        particleContainer.push_back(new Particle((float)xpos, (float)ypos));
    }
}

void TestParticle::OnRender()
{
    GLErrCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLErrCall(glClear(GL_COLOR_BUFFER_BIT));
    renderer renderer;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

    for (size_t i = 0; i < particleContainer.size(); i++)
    {
        particleContainer[i]->addRot(0.001f);
        m_proj = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f);

        m_model = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.0f));
        m_model = glm::rotate(m_model, glm::radians(particleContainer[i]->getRot()), glm::vec3(0.0f, 0.0f, 1.0f));
        m_model = glm::scale(m_model, glm::vec3(1.f, 1.f, 1.f));

        glm::mat4 u_MVP = m_proj * m_view * m_model;

        particleContainer[i]->m_shader->Bind();
        particleContainer[i]->m_shader->setUniformMat4f("u_MVP", u_MVP);

        particleContainer[i]->m_va->Bind();
        particleContainer[i]->m_ib->Bind();

        renderer.Draw(*particleContainer[i]->m_va, *particleContainer[i]->m_ib, *particleContainer[i]->m_shader);

        particleContainer[i]->m_shader->UnBind();
        particleContainer[i]->m_va->UnBind();
        particleContainer[i]->m_ib->UnBind();
    }
}

void TestParticle::OnImGuiRender()
{
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // namespace test