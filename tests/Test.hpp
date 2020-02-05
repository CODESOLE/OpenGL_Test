#pragma once
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include "./../dep/imgui/imgui.h"
#include "./../src/Transform.hpp"
#include <GLFW/glfw3.h>

namespace test
{
class Test
{
public:
    Test();
    virtual ~Test();
    virtual void OnUpdate(float deltaTime, GLFWwindow *window, double xpos, double ypos);
    virtual void OnRender();
    virtual void OnImGuiRender();
};

class TestMenu : Test
{
private:
    std::vector<std::pair<std::string, std::function<Test *()>>> m_TestOptions;
    Test *&m_currentTest;

public:
    TestMenu(Test *&currenctTestPointer);
    void OnImGuiRender() override;

    template <typename T>
    void RegisterTest(const std::string &name)
    {
        std::cout << "Registering test " << '[' << name << ']' << std::endl;
        m_TestOptions.push_back(std::make_pair(name, []() { return new T(); }));
    }
};

} // namespace test