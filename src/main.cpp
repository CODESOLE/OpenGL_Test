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

using namespace std::string_literals;
#define MAIN
#ifdef MAIN

/*  if (color.r >= 1.0f)
                inc = -0.0001f;
            else if (color.r <= 0.0f)
                inc = 0.0001f;

            color.r += inc;
            color.g += inc;
            color.b += inc; */
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        ImGui_ImplGlfwGL3_Shutdown();
        ImGui::DestroyContext();
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void)
{
    GLFWwindow *window;
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1024, 768, "GL Example", NULL, NULL);

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

    {

        GLErrCall(glEnable(GL_BLEND));
        GLErrCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLErrCall(glBlendEquation(GL_FUNC_ADD));

        int w, h;

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

        while (!glfwWindowShouldClose(window))
        {

            glfwGetFramebufferSize(window, &w, &h); //auto scale frame size
            glViewport(0, 0, w, h);                 //auto scale frame size

            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();

            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
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
        }
        delete currentTest;
        if (currentTest != (test::Test *)test_menu)
            delete test_menu;
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
#else
//vertex shader kaynak kodu
const char *vssource =
    R"(#version 330 core\n                              
 layout (location = 0) in vec3 inPosition;              
 void main()                                                
 {                                                      
    gl_Position = vec4(inPosition, 1.0);                
 })";
//fragment shader kaynak kodu
const char *fssource =
    R"(#version 330 core\n                           
 out vec4 fragColor;                                 
 void main()                                         
 {                                                   
    fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);        
 })";

//noktalara ait koordinat bilgileri.
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f};

//OpenGL nesnelerinin id değerlerini tutacak olan değişkenler
unsigned int fragmentShader;
unsigned int vertexShader;
unsigned int shaderProgram;
unsigned int VBO;
unsigned int VAO;

int main(int argc, char **argv)
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(600, 600, "İLk Programım", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Pencere Olusturulamadi" << std::endl;

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error happend!";

    //vertex shader oluşsturuluyor
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vssource, NULL);
    glCompileShader(vertexShader);

    //Fragment Shader Oluşturuluyor
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fssource, NULL);
    glCompileShader(fragmentShader);

    //Program nesnesi oluşturuluyor ve shader nesneleri yükleniyor
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    ShaderProgram shader(vssource, fssource);

    unsigned int IndexBuffer;
    unsigned int indecies[] = {0, 1, 2, 2, 3, 0};
    //vertex array object oluşturuluyor
    glGenVertexArrays(1, &VAO);
    //vertex buffer object oluşuruluyor
    //glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO);

    glGenBuffers(1, &IndexBuffer);

    //vertex array object aktif edildi.
    glBindVertexArray(VAO);
    //vertex buffer nesnesi aktif edildi.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //vertex buffer'a nokta bilgileri yollanıyor
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    //gönderilen vertex'e ait özellikler etiketleniyor
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    //özellik  etiket i aktif ediliyor.
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indecies[0], GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window))
    {
        //oluşturulacak resim başlangıç rengine boyanıyor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        glUseProgram(shaderProgram);
        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}
#endif