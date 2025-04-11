#pragma once
#pragma once
#include <glad/glad.h> 
#include "GLFW/glfw3.h"

class SinglePointShader
{
public:
	SinglePointShader() {
		this->vertexShaderCode[0] =
		{
			"#version 460 core \n"
			"void main(void) { \n"
			"gl_position = vec4(0.0,0.0,0.5,1.0);\n"
			"}\n"
		};

		this->fragmentShaderCode[0] =
		{
			"#version 460 core \n"
			"out vec4 color; \n"
			"void main(void) { \n"
			"color = vec4(0.0,0.8,1.0,1.0);\n"
			"}\n"
		};

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, this->vertexShaderCode, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, this->fragmentShaderCode, NULL);
		glCompileShader(fragmentShader);

		this->shader = glCreateProgram();
		glAttachShader(shader, vertexShader);
		glAttachShader(shader, fragmentShader);
		glLinkProgram(this->shader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);
	}

	inline GLuint GetProgram() const { return shader; }

	~SinglePointShader() {
		glDeleteProgram(shader);
		glDeleteVertexArrays(1, &vertexArrayObject);
	}
private:
	const GLchar* vertexShaderCode[1];
	const GLchar* fragmentShaderCode[1];
	GLuint shader;
	GLuint vertexArrayObject;

};

