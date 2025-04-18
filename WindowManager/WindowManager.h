#pragma once
#include "pch.h"

#include <memory>
#include <cmath>
#include "glad/glad.h"

#include "SinglePointShader.h"


namespace WindowManagement {

    class WindowManager
    {
    private:
        struct DestroyglfwWin {

            void operator()(GLFWwindow* ptr) {
                glfwDestroyWindow(ptr);
            }

        };
    private:
        std::unique_ptr<GLFWwindow, DestroyglfwWin> managedOpenGLWindow;
        Shaders::SinglePointShader pointShaderProgram;
        Shaders::TriangleShader triangleShaderProgram;

    public:

        WindowManager() {
            managedOpenGLWindow = std::unique_ptr<GLFWwindow, DestroyglfwWin>(glfwCreateWindow(500, 500, "My first window in OpenGL", NULL, NULL));

            if (!managedOpenGLWindow.get())
                throw(std::exception("Failed to open window"));

            glfwMakeContextCurrent(managedOpenGLWindow.get());
            glfwSetFramebufferSizeCallback(managedOpenGLWindow.get(), WindowManagement::WindowManager::FramebufferSizeCallback);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                throw(std::exception("Failed to initialize GLAD"));

            InitializePoint();
            InitializeTriangle();
        }

        ~WindowManager() {

        }

        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }

        inline GLFWwindow* GetManagedWindowPointer() const { return managedOpenGLWindow.get(); }

        void Render(const double colorValueToProcess) const;

        void InitializePoint();

        void InitializeTriangle();

        void ListenProgramEnd()
        {
            if (glfwGetKey(managedOpenGLWindow.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(managedOpenGLWindow.get(), true);
        }

        inline void ProcessEvents() const {
            glfwPollEvents();
        }

        bool EndWindow() const {
            return !glfwWindowShouldClose(managedOpenGLWindow.get());
        }
    };
}