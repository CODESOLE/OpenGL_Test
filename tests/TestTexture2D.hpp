#pragma once
#include "Test.hpp"

#include "./../src/VertexArray.hpp"
#include "./../src/VertexBuffer.hpp"
#include "./../src/IndexBuffer.hpp"
#include "./../src/Texture.hpp"
#include <memory>

namespace test
{
class TestTexture2D : public Test
{
private:
    float m_f = 0.0f, m_f2 = 0.0f;
    std::unique_ptr<VertexArray> m_va;
    std::unique_ptr<VertexBuffer> m_vb;
    std::unique_ptr<IndexBuffer> m_ib;
    std::unique_ptr<ShaderProgram> m_shader;
    std::unique_ptr<Texture> m_texture;
    glm::mat4 m_proj, m_view, m_view2;
    int w, h;

public:
    TestTexture2D();
    ~TestTexture2D();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;
};

} // namespace test