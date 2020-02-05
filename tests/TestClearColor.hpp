#pragma once

#include "Test.hpp"
#include <GLFW/glfw3.h>

namespace test
{
class TestClearColor : public Test
{
private:
    float m_ClearColor[4];

public:
    TestClearColor();
    ~TestClearColor();

    void OnUpdate(float deltaTime, GLFWwindow *window, double xpos, double ypos, double xoffset, double yoffset) override;
    void OnRender() override;
    void OnImGuiRender() override;
};

} // namespace test