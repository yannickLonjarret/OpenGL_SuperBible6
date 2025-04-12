// openGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once
#include "WindowManager.h"
#include "GLFW/glfw3.h"
#include <cmath>

void InitializeOpenGLToolkit() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwInit();
}

void EndOpenGLToolkit() {
    glfwTerminate();
}
int main()
{
    InitializeOpenGLToolkit();

    WindowManagement::WindowManager window = WindowManagement::WindowManager();

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
