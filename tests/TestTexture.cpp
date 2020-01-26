#include "TestTexture2D.hpp"
#include "./../src/renderer.hpp"
#include "./../dep/imgui/imgui.h"

namespace test
{

TestTexture2D::TestTexture2D()
{
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
}

void TestTexture2D::OnImGuiRender()
{
}

} // namespace test