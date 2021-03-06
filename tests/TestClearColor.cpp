#include "TestClearColor.hpp"
#include "./../src/renderer.hpp"
#include "./../dep/imgui/imgui.h"

namespace test
{
TestClearColor::TestClearColor(/* args */) : m_ClearColor{0.0f, 0.0f, 0.0f, 0.0f}
{
}

TestClearColor::~TestClearColor()
{
}

void TestClearColor::OnUpdate(float deltaTime, GLFWwindow *window, double xpos, double ypos, double xoffset, double yoffset)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void TestClearColor::OnRender()
{
    GLErrCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
    GLErrCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestClearColor::OnImGuiRender()
{
    ImGui::ColorEdit4("glClearColor Value: ", m_ClearColor);
}

} // namespace test
