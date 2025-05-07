#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
    GLFWwindow* window = glfwCreateWindow(800, 800, "Motion Capture Viewer", nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    // Move window to current context
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 800, 800);

    while(!glfwWindowShouldClose(window)) {

        // Rendering commands
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: Add drawing logic here

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}