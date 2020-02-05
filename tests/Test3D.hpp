#pragma once
#include "Test.hpp"

#include "./../src/VertexArray.hpp"
#include "./../src/VertexBuffer.hpp"
#include "./../src/IndexBuffer.hpp"
#include "./../src/Texture.hpp"
#include <memory>

namespace test
{
class Test3D : public Test
{
private:
    float m_camPX = 0.0f, m_camPY = 0.0f, m_camPZ = 500.0f,
          m_camRX = 0.0f, m_camRY = 0.0f, m_camRZ = 0.0f,
          m_modelPX = 0.0f, m_modelPY = 0.0f, m_modelPZ = 0.0f,
          m_modelRX = 0.0f, m_modelRY = 0.0f, m_modelRZ = 0.0f,
          m_modelSX = 1.0f, m_modelSY = 1.0f, m_modelSZ = 1.0f;

    std::unique_ptr<VertexArray> m_va;
    std::unique_ptr<VertexBuffer> m_vb;
    std::unique_ptr<IndexBuffer> m_ib;
    std::unique_ptr<ShaderProgram> m_shader;
    glm::mat4 m_proj, m_camView, m_modelT, u_MVP;
    glm::vec3 m_camPos, m_camLookAt, m_camUp;
    int w, h;
    float lastX, lastY;
    bool firstMouse;
    double yaw, pitch;

public:
    Test3D();
    ~Test3D();

    void OnUpdate(float deltaTime, GLFWwindow *window, double xpos, double ypos) override;
    void OnRender() override;
    void OnImGuiRender() override;
};

} // namespace test