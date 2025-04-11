// openGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once
#include <glad/glad.h> 
#include <iostream>
#include "GLFW/glfw3.h"
#include "SinglePointShader.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

class WindowManager {
private:
    struct DestroyglfwWin {

        void operator()(GLFWwindow* ptr) {
            glfwDestroyWindow(ptr);
        }

    };
private:
    std::unique_ptr<GLFWwindow, DestroyglfwWin> managedOpenGLWindow;
    SinglePointShader shaderProgram;


public:

    WindowManager(){
        managedOpenGLWindow = std::unique_ptr<GLFWwindow, DestroyglfwWin>(glfwCreateWindow(500, 500, "My first window in OpenGL", NULL, NULL));

        if (!managedOpenGLWindow.get())
            throw(std::exception("Failed to open window"));
        
        glfwMakeContextCurrent(managedOpenGLWindow.get());
        glfwSetFramebufferSizeCallback(managedOpenGLWindow.get(), FramebufferSizeCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw(std::exception("Failed to initialize GLAD"));
        
    }

    ~WindowManager() {

    }

    GLFWwindow* GetManagedWindowPointer() const {
        return managedOpenGLWindow.get();
    }

    void Render(const double colorValueToProcess) const {
        GLfloat colors[] = { std::cos(colorValueToProcess), std::sin(colorValueToProcess), 0., 1.0f};
        glClearBufferfv(GL_COLOR, 0, colors) ;
        glfwSwapBuffers(managedOpenGLWindow.get());
    }

    void ListenProgramEnd()
    {
        if (glfwGetKey(managedOpenGLWindow.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(managedOpenGLWindow.get(), true);
    }

    void ProcessEvents() {
        glfwPollEvents();
    }

    bool EndWindow() {
        return !glfwWindowShouldClose(managedOpenGLWindow.get());
    }

    
};


void InitializeOpenGLToolkit() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwInit();
}

void EndOpenGLToolkit() {
    glfwTerminate();
}
int main()
{
    InitializeOpenGLToolkit();

    WindowManager window = WindowManager();

    double smallSteps = 0.;
    while (window.EndWindow()){

        window.ListenProgramEnd();
        window.Render(smallSteps);
        window.ProcessEvents();

        smallSteps += 1.e-4;
        if (smallSteps > _HUGE_ENUF)
            smallSteps = 0.0;
 
    } 
    EndOpenGLToolkit();
    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
