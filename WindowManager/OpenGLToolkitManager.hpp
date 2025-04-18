#pragma once

#include "GLFW/glfw3.h"

namespace OpenGLToolkitManager {
    void InitializeOpenGLToolkit() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwInit();
    }

    void EndOpenGLToolkit() {
        glfwTerminate();
    }

}