#include "WindowManager.h"
#include "WindowManager.h"
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
        for (const auto& shader : shaders) {
            shader->Draw();
        }
        glfwSwapBuffers(managedOpenGLWindow.get());
    }

    void WindowManager::RenderMovingTriangle(const double colorValueToProcess) const
    {
        GLfloat colors[] = { 0.,0.,0.,0.};
        GLfloat magenta[] = { 1.f, 0.f, 1.f, 1. };
        glClearBufferfv(GL_COLOR, 0, colors);

        GLfloat triangleColor[] = { std::cos(colorValueToProcess), std::sin(colorValueToProcess), 0., 1.0f };
        GLfloat position1[] = { std::cos(colorValueToProcess) * 0.5, std::sin(colorValueToProcess) * 0.5, 0., 0. };
        GLfloat position2[] = { std::sin(colorValueToProcess) * 0.5, std::cos(colorValueToProcess) * 0.5, 0., 0. };
        //shaderProgram.SetPointSize(40* std::cos(colorValueToProcess));
        shaders.at(0)->Draw(position1, triangleColor);
        shaders.at(1)->Draw(position2, triangleColor);
        if (shaders.size() > 2) {
            shaders.at(4)->Draw();
            shaders.at(2)->TesselateDraw();
            shaders.at(3)->TesselateDraw();
            
        }
        glfwSwapBuffers(managedOpenGLWindow.get());
    }

    void WindowManager::InitializePoint()
    {
        std::unique_ptr<Shaders::Shader> pointShaderProgram = std::make_unique<Shaders::SinglePointShader>(
            "#version 460 core \n"
            "void main(void) \n"
            "{ \n"
            "	gl_Position = vec4(0.5,0.5,0.5,1.0);\n"
            "}\n\0",
            "#version 460 core \n"
            "out vec4 color; \n"
            "void main(void) { \n"
            "	color = vec4(0.5,0.,0.,1.);\n"
            "}\n\0");

        if (auto* singlePointShader = dynamic_cast<Shaders::SinglePointShader*>(pointShaderProgram.get())) {
            singlePointShader->SetPointSize(40.f);
        }
        shaders.push_back(std::move(pointShaderProgram));
    }

    void WindowManager::InitializeTriangle()
    {
        std::unique_ptr<Shaders::Shader> triangleShaderProgram = std::make_unique<Shaders::TriangleShader>(
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
        shaders.push_back(std::move(triangleShaderProgram));
    }

    void WindowManager::InitializeOffsetTriangle()
    {
        std::unique_ptr<Shaders::Shader> triangleShaderProgram = std::make_unique<Shaders::TriangleShader>(
            "#version 460 core                                                 \n"
            "                                                                  \n"
            "layout (location = 0) in vec4 offset;                             \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),\n"
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
        shaders.push_back(std::move(triangleShaderProgram));
    }

    void WindowManager::InitializeOffsetColorTriangle()
    {
        std::unique_ptr<Shaders::Shader> triangleShaderProgram = std::make_unique<Shaders::TriangleShader>(
            "#version 460 core                                                 \n"
            "                                                                  \n"
            "layout (location = 0) in vec4 offset;                             \n"
            "layout (location = 1) in vec4 color;                              \n"
            "out vec4 vs_color;                                                 \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),\n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "                                                                  \n"
            "    gl_Position = vertices[gl_VertexID] + offset;                 \n"
            "    vs_color = color;                                             \n"
            "}                                                                 \n\0",

            "#version 460 core                                                 \n"
            "                                                                  \n"
            "in vec4 vs_color;                                                 \n"
            "out vec4 color;                                                   \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    color = vs_color;                                             \n"
            "}                                                                 \n\0");
        shaders.push_back(std::move(triangleShaderProgram));
    }

    void WindowManager::InitializeInterfaceBlockTriangle()
    {
        std::unique_ptr<Shaders::Shader> triangleShaderProgram = std::make_unique<Shaders::TriangleShader>(
            "#version 460 core                                                 \n"
            "                                                                  \n"
            "layout (location = 0) in vec4 offset;                             \n"
            "layout (location = 1) in vec4 color;                              \n"
            "out VS_OUT                                                        \n"
            "{                                                                 \n"
            "   vec4 vs_color;                                                 \n"
            "} vs_out;                                                         \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),\n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "                                                                  \n"
            "    gl_Position = vertices[gl_VertexID] + offset;                 \n"
            "    vs_out.color = color;                                         \n"
            "}                                                                 \n\0",

            "#version 460 core                                                 \n"
            "                                                                  \n"
            "in VS_OUT                                                         \n"
            "{                                                                 \n"
            "   vec4 color;                                                    \n"
            "} fs_in;                                                          \n"
            "out vec4 color;                                                   \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    color = fs_in.color;                                          \n"
            "}                                                                 \n\0");
        shaders.push_back(std::move(triangleShaderProgram));
    }
    void WindowManager::InitializeTesselationTriangle()
    {
        std::unique_ptr<Shaders::Shader> triangleShaderProgram = std::make_unique<Shaders::TriangleShader>(
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
            "#version 460 core                                                                 \n"
            "                                                                                  \n"
            "layout (vertices = 3) out;                                                        \n"
            "                                                                                  \n"
            "void main(void)                                                                   \n"
            "{                                                                                 \n"
            "    if (gl_InvocationID == 0)                                                     \n"
            "    {                                                                             \n"
            "        gl_TessLevelInner[0] = 5.0;                                               \n"
            "        gl_TessLevelOuter[0] = 5.0;                                               \n"
            "        gl_TessLevelOuter[1] = 5.0;                                               \n"
            "        gl_TessLevelOuter[2] = 5.0;                                               \n"
            "    }                                                                             \n"
            "    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     \n"
            "}                                                                                 \n\0",
            "#version 460 core                                                                 \n"
            "                                                                                  \n"
            "layout (triangles, equal_spacing, cw) in;                                         \n"
            "                                                                                  \n"
            "void main(void)                                                                   \n"
            "{                                                                                 \n"
            "    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       \n"
            "                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       \n"
            "                  (gl_TessCoord.z * gl_in[2].gl_Position);                        \n"
            "}                                                                                 \n\0",
            "#version 460 core                                                 \n"
            "                                                                  \n"
            "out vec4 color;                                                   \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    color = vec4(1.0, 0.0, 1.0, 0.0);                             \n"
            "}                                                                 \n\0");
        shaders.push_back(std::move(triangleShaderProgram));
    }
    void WindowManager::InitializeTesselationGeometryTriangle()
    {
        std::unique_ptr<Shaders::Shader> triangleShaderProgram = std::make_unique<Shaders::TriangleShader>(
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
            "#version 460 core                                                                 \n"
            "                                                                                  \n"
            "layout (vertices = 3) out;                                                        \n"
            "                                                                                  \n"
            "void main(void)                                                                   \n"
            "{                                                                                 \n"
            "    if (gl_InvocationID == 0)                                                     \n"
            "    {                                                                             \n"
            "        gl_TessLevelInner[0] = 5.0;                                               \n"
            "        gl_TessLevelOuter[0] = 5.0;                                               \n"
            "        gl_TessLevelOuter[1] = 5.0;                                               \n"
            "        gl_TessLevelOuter[2] = 5.0;                                               \n"
            "    }                                                                             \n"
            "    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     \n"
            "}                                                                                 \n\0",
            "#version 460 core                                                                 \n"
            "                                                                                  \n"
            "layout (triangles, equal_spacing, cw) in;                                         \n"
            "                                                                                  \n"
            "void main(void)                                                                   \n"
            "{                                                                                 \n"
            "    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       \n"
            "                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       \n"
            "                  (gl_TessCoord.z * gl_in[2].gl_Position);                        \n"
            "}                                                                                 \n\0",
            "#version 460 core                                                 \n"
            "                                                                  \n"
            "layout (triangles) in;                                            \n"
            "layout (points, max_vertices = 3) out;                            \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    int i;                                                        \n"
            "    for(i = 0; i < gl_in.length();i++){                           \n"
            "    gl_Position = gl_in[i].gl_Position;                           \n"
            "    EmitVertex();                                                 \n"
            "    }                                                             \n"
            "}                                                                 \n\0",
            "#version 460 core                                                 \n"
            "                                                                  \n"
            "out vec4 color;                                                   \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    color = vec4(0.0, 1.0, 0.0, 0.0);                             \n"
            "}                                                                 \n\0");
        shaders.push_back(std::move(triangleShaderProgram));
    }
    void WindowManagement::WindowManager::InitializeFragmentTriangle()
    {
        std::unique_ptr<Shaders::Shader> triangleShaderProgram = std::make_unique<Shaders::TriangleShader>(
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
            "out vec4 color;                                                 \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    color = vec4(sin(gl_FragCoord.x *0.25) *0.5+0.5,\n"
            "                 cos(gl_FragCoord.y *0.25) *0.5+0.5,\n"
            "                 sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y *0.15),\n"
                              "1.0);\n"
            "}                                                                 \n\0");
        shaders.push_back(std::move(triangleShaderProgram));
    }
    void WindowManagement::WindowManager::InitializeMovingFragmentTriangle()
    {
        std::unique_ptr<Shaders::Shader> triangleShaderProgram = std::make_unique<Shaders::TriangleShader>(
            "#version 460 core                                                          \n"
            "                                                                           \n"
            "layout (location = 0) in vec4 offset;                             \n"
            "layout (location = 1) in vec4 color;                              \n"
            "out vec4 vs_color; \n"
            "void main(void)                                                            \n"
            "{                                                                          \n"
            "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),           \n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),           \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0));          \n"
            "    const vec4 colors[] = vec4[](vec4(1.0, 0.0, 0.0, 1.0),                 \n"
            "                                 vec4(0.0, 1.0, 0.0, 1.0),                 \n"
            "                                 vec4(0.0, 0.0, 1.0, 1.0));                \n"
            "                                                                           \n"
            "    gl_Position = vertices[gl_VertexID] + offset;                                   \n"
            "    vs_color = colors[gl_VertexID] + color;                                        \n"
            "}                                                                          \n\0",

            "#version 460 core                                                 \n"
            "                                                                  \n"
            "in vec4 vs_color;                                                 \n"
            "out vec4 color;                                                   \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    color = vs_color;                                             \n"
            "}                                                                 \n\0");
        shaders.push_back(std::move(triangleShaderProgram));
    }
}