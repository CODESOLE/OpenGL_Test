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
using namespace std::string_literals;
#define cherno
#ifdef cherno
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

    window = glfwCreateWindow(640, 480, "GL Example", NULL, NULL);

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
        float verticesss[] = {
            0.0f, 100.0f, 0.0f, 0.0f,
            100.0f, 100.0f, 1.0f, 0.0f,
            100.0f, 200.0f, 1.0f, 1.0f,
            0.0f, 200.0f, 0.0f, 1.0f};

        unsigned int VertexArrayObject;
        unsigned int indecies[] = {0, 1, 2, 2, 3, 0};

        GLErrCall(glEnable(GL_BLEND));
        GLErrCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLErrCall(glBlendEquation(GL_FUNC_ADD));

        VertexArray va;
        VertexBuffer vb(verticesss, sizeof(verticesss));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indecies, 6);

        va.UnBind();
        vb.UnBind();
        ib.UnBind();

        ShaderProgram sp1("./../shaders/VertexShader.vert", "./../shaders/FragmentShader.frag");
        sp1.UnBind();
        glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
        int w, h;
        float inc;

        renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        Texture texture("./../res/arduino.png");
        texture.Bind();

        while (!glfwWindowShouldClose(window))
        {
            ImGui_ImplGlfwGL3_NewFrame();

            glfwGetFramebufferSize(window, &w, &h); //auto scale frame size
            glViewport(0, 0, w, h);                 //auto scale frame size

            //inc = ((float)w) / ((float)h);

            renderer.Clear();
            static float f = 0.0f, f2 = 0.0f;
            sp1.Bind();
            sp1.setUniformInt1("u_Texture", 0); //this zero should be matching with the texture.Bind() argument

            glm::mat4 proj = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f);
            glm::mat4 view = glm::translate(glm::mat4(1), glm::vec3(f, 0.0f, 0.0f));
            glm::mat4 u_MVP = proj * view;
            sp1.setUniformMat4f("u_MVP", u_MVP);

            //sp1.setUniformFloat4("u_Color", color);
            va.Bind();
            ib.Bind();
            renderer.Draw(va, ib, sp1);

            glm::mat4 view2 = glm::translate(glm::mat4(1), glm::vec3(f2, 100.0f, 0.0f));
            u_MVP = proj * view2;
            sp1.setUniformMat4f("u_MVP", u_MVP);

            renderer.Draw(va, ib, sp1);

            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, (float)w - 100.0f);
            ImGui::SliderFloat("float2", &f2, 0.0f, (float)w - 100.0f);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
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