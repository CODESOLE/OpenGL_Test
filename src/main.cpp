#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "ShaderProgram.hpp"
#include "./../dep/glm/vec3.hpp"
#include "./../dep/glm/vec4.hpp"
#include "./../dep/glm/glm.hpp"
#include "./../dep/glm/gtc/matrix_transform.hpp"
#include <cmath>
#include <vector>
#include <signal.h>
#include "renderer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Texture.hpp"
#include "./../dep/imgui/imgui.h"
#include "./../dep/imgui/imgui_impl_glfw_gl3.h"
#include "./../tests/TestClearColor.hpp"
#include "./../tests/TestTexture2D.hpp"
#include "./../tests/Test3D.hpp"
#include "./../tests/TestParticle.hpp"

using namespace std::string_literals;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

double xxpos, yypos, scrllX = 0.0, scrllY = 0.0;

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    xxpos = xpos;
    yypos = ypos;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    scrllX = xoffset;
    scrllY = yoffset;
}

int main(void)
{
    GLFWwindow *window;
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(600, 480, "GL Example", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //V-sync

    if (glewInit() != GLEW_OK)
        std::cout << "Error happend!";

    std::cout << "GL_VERSION: "
              << glGetString(GL_VERSION) << '\n';
    std::cout << "GL_VENDOR: "
              << glGetString(GL_VENDOR)
              << '\n';
    std::cout << "GL_RENDERER: "
              << glGetString(GL_RENDERER)
              << '\n';
    std::cout << "GLEW_VERSION: "
              << glewGetString(GLEW_VERSION) << '\n';
    std::cout << "GLFW_VERSION: "
              << glfwGetVersionString() << '\n'
              << '\n';

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    int w, h;

    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    {

        GLErrCall(glEnable(GL_BLEND));
        GLErrCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLErrCall(glBlendEquation(GL_FUNC_ADD));

        renderer renderer;

        test::Test *currentTest = nullptr;
        test::TestMenu *test_menu = new test::TestMenu(currentTest);
        currentTest = (test::Test *)test_menu;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        test_menu->RegisterTest<test::TestClearColor>("Clear Color Test");
        test_menu->RegisterTest<test::TestTexture2D>("Texture 2D Test");
        test_menu->RegisterTest<test::Test3D>("3D Test");
        test_menu->RegisterTest<test::TestParticle>("Particle Test");

        while (!glfwWindowShouldClose(window))
        {

            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            glfwGetFramebufferSize(window, &w, &h); //auto scale frame size
            glViewport(0, 0, w, h);                 //auto scale frame size

            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();

            if (currentTest)
            {
                currentTest->OnUpdate(deltaTime, window, xxpos, yypos, scrllX, scrllY);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != (test::Test *)test_menu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = (test::Test *)test_menu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        } //while End
        delete currentTest;
        if (currentTest != (test::Test *)test_menu)
            delete test_menu;

        ImGui_ImplGlfwGL3_Shutdown();
        ImGui::DestroyContext();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}