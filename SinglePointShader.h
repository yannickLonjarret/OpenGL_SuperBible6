#pragma once
#pragma once
#include <glad/glad.h> 
#include "GLFW/glfw3.h"

class SinglePointShader
{
public:
	SinglePointShader(): shader(NULL), vertexArrayObject(NULL) {}

	SinglePointShader(const GLchar* vertex, const GLchar* fragment) {
		const GLchar* vertexShaderCode = vertex;

		const GLchar* fragmentShaderCode = fragment;
		
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
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
	GLuint shader;
	GLuint vertexArrayObject;

};

