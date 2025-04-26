#include "pch.h"
#include "WindowManager.h"
#include <memory>
#include <cmath>

namespace WindowManagement {

    void WindowManager::Render(const double colorValueToProcess) const
    {
        GLfloat colors[] = { std::cos(colorValueToProcess), std::sin(colorValueToProcess), 0., 1.0f };
        glClearBufferfv(GL_COLOR, 0, colors);

        //shaderProgram.SetPointSize(40* std::cos(colorValueToProcess));
        triangleShaderProgram.DrawTriangle();
        pointShaderProgram.DrawPoint();
        
        glfwSwapBuffers(managedOpenGLWindow.get());
    }

    void WindowManager::InitializePoint()
    {
        pointShaderProgram = Shaders::SinglePointShader("#version 460 core \n"
            "void main(void) \n"
            "{ \n"
            "	gl_Position = vec4(0.5,0.5,0.5,1.0);\n"
            "}\n\0",
            "#version 460 core \n"
            "out vec4 color; \n"
            "void main(void) { \n"
            "	color = vec4(0.5,0.,0.,1.);\n"
            "}\n\0");
        pointShaderProgram.SetPointSize(40.);
    }

    void WindowManager::InitializeTriangle()
    {
        triangleShaderProgram = Shaders::TriangleShader(
            "#version 460 core                                                 \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "                                                                  \n"
            "    gl_Position = vertices[gl_VertexID];                          \n"
            "}                                                                 \n\0",
            "#version 460 core                                                 \n"
            "                                                                  \n"
            "out vec4 color;                                                   \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    color = vec4(0.0, 0.8, 1.0, 1.0);                             \n"
            "}                                                                 \n\0");
    }

    void WindowManager::InitializeOffsetTriangle()
    {
        triangleShaderProgram = Shaders::TriangleShader(
            "#version 460 core                                                 \n"
            "                                                                  \n"
            "layout (location = 0) in vec4 offset                              \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "                                                                  \n"
            "    gl_Position = vertices[gl_VertexID] + offset;                 \n"
            "}                                                                 \n\0",
            "#version 460 core                                                 \n"
            "                                                                  \n"
            "out vec4 color;                                                   \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    color = vec4(0.0, 0.8, 1.0, 1.0);                             \n"
            "}                                                                 \n\0");
    }
}