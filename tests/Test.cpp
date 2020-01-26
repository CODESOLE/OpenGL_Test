#include "Test.hpp"

namespace test
{
Test::Test() {}
Test::~Test() {}
void Test::OnUpdate(float deltaTime) {}
void Test::OnRender() {}
void Test::OnImGuiRender() {}

TestMenu::TestMenu(Test *&currenctTestPointer) : m_currentTest(currenctTestPointer)
{
}

void TestMenu::OnImGuiRender()
{
    for (auto &test : m_TestOptions)
    {
        if (ImGui::Button(test.first.c_str()))
            m_currentTest = test.second();
    }
}

} // namespace test