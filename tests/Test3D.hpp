#pragma once
#include "Test.hpp"

#include "./../src/VertexArray.hpp"
#include "./../src/VertexBuffer.hpp"
#include "./../src/IndexBuffer.hpp"
#include "./../src/Texture.hpp"
#include "./../src/Camera.hpp"
#include <memory>

namespace test
{
class Test3D : public Test
{
private:
    std::unique_ptr<VertexArray> m_va;
    std::unique_ptr<VertexBuffer> m_vb;
    std::unique_ptr<IndexBuffer> m_ib;
    std::unique_ptr<ShaderProgram> m_shader;
    glm::mat4 m_proj, m_camView, m_modelT, u_MVP;
    glm::vec3 m_camPos, m_camLookAt, m_camUp;
    int w, h;
    float lastX, lastY;
    bool firstMouse;
    double yaw, pitch, fov;
    Camera camera;

public:
    Test3D();
    ~Test3D();

    void OnUpdate(float deltaTime, GLFWwindow *window, double xpos, double ypos, double xoffset, double yoffset) override;
    void OnRender() override;
    void OnImGuiRender() override;
};

} // namespace test