#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
#include <iostream>
#include <cmath>

#include "EBO.h"
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   800



GLfloat vertices[] = 
{
   -0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f,     0.8f, 0.3f, 0.02f,
    0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f,     0.8f, 0.3f, 0.02f,
    0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f, 0.32f,
   -0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,     0.9f, 0.5f, 0.17f,
    0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,     0.9f, 0.5f, 0.17f,
    0.0f, -0.5f * float(sqrt(3)) / 3,     0.0f,     0.8f, 0.3f, 0.02f
};

GLuint indices[] = 
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

int main() {
    if(!glfwInit()) {
        std::cerr << "Failed to initialize glfw\n";
        return -1;
    }

    // GLFW Config: OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Create Window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Motion Capture Viewer", nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    // Move window to current context
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    Shader shaderprogram("shaders/default.vert", "shaders/default.frag");

    // Vertex Array Object
    VAO vao;
    vao.Bind();

    // Vertex Buffer Object
    VBO vbo(vertices, sizeof(vertices));

    // Element Buffer Object
    EBO ebo(indices, sizeof(indices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // unbind all objects
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    while(!glfwWindowShouldClose(window)) {

        // Rendering commands
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: Add drawing logic here

        shaderprogram.Activate();
        vao.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents(); // responsive window
    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderprogram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}