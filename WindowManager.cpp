#include "WindowManager.h"

namespace WindowManagement {

    void WindowManager::Render(const double colorValueToProcess) const
    {
        GLfloat colors[] = { std::cos(colorValueToProcess), std::sin(colorValueToProcess), 0., 1.0f };
        glClearBufferfv(GL_COLOR, 0, colors);

        //shaderProgram.SetPointSize(40* std::cos(colorValueToProcess));
        shaderProgram.DrawPoint();
        glfwSwapBuffers(managedOpenGLWindow.get());
    }

    void WindowManager::InitializePoint()
    {
        shaderProgram = SinglePointShader("#version 460 core \n"
            "void main(void) \n"
            "{ \n"
            "	gl_Position = vec4(0.5,0.5,0.5,1.0);\n"
            "}\n\0",
            "#version 460 core \n"
            "out vec4 color; \n"
            "void main(void) { \n"
            "	color = vec4(0.5,0.,0.,1.);\n"
            "}\n\0");
        shaderProgram.SetPointSize(40.);
    }
}