#pragma once
#ifdef WINDOWMANAGER_EXPORTS
#define WM_API __declspec(dllexport)
#else
#define WM_API __declspec(dllimport)
#endif // WINDOWMANAGER_EXPORTS

#include "pch.h"
#include <memory>
#include <cmath>
#include "glad/glad.h"

#include "SinglePointShader.h"
#include "OpenGLToolkitManager.hpp"
#include <vector>


namespace WindowManagement {


    class WM_API WindowManager
    {
    private:
        struct DestroyglfwWin {

            void operator()(GLFWwindow* ptr) {
                glfwDestroyWindow(ptr);
            }

        };
    private:
        std::unique_ptr<GLFWwindow, DestroyglfwWin> managedOpenGLWindow;
        std::vector<std::unique_ptr<Shaders::Shader>> shaders;

    public:

        WindowManager() {
            shaders = std::vector< std::unique_ptr<Shaders::Shader>>();

            OpenGLToolkitManager::InitializeOpenGLToolkit();
            managedOpenGLWindow = std::unique_ptr<GLFWwindow, DestroyglfwWin>(glfwCreateWindow(500, 500, "My first window in OpenGL", NULL, NULL));

            if (!managedOpenGLWindow.get())
                throw(std::exception("Failed to open window"));

            glfwMakeContextCurrent(managedOpenGLWindow.get());
            glfwSetFramebufferSizeCallback(managedOpenGLWindow.get(), WindowManagement::WindowManager::FramebufferSizeCallback);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                throw(std::exception("Failed to initialize GLAD"));
        }

        ~WindowManager() {
            OpenGLToolkitManager::EndOpenGLToolkit();
        }

        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }

        inline GLFWwindow* GetManagedWindowPointer() const { return managedOpenGLWindow.get(); }

        void Render(const double colorValueToProcess) const;
        
        void RenderMovingTriangle(const double colorValueToProcess) const;

        void InitializePoint();

        void InitializeTriangle();

        void InitializeOffsetTriangle();

        void InitializeOffsetColorTriangle();

        void InitializeInterfaceBlockTriangle();

        void InitializeTesselationTriangle();

        void InitializeTesselationGeometryTriangle();

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