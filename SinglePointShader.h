#pragma once
#include <glad/glad.h> 
#include "GLFW/glfw3.h"

namespace Shaders {

	class SinglePointShader
	{
	public:
		SinglePointShader() = default;

		SinglePointShader(const GLchar* vertex, const GLchar* fragment) {

			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertex, NULL);
			glCompileShader(vertexShader);

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragment, NULL);
			glCompileShader(fragmentShader);

			this->shader = glCreateProgram();
			glAttachShader(this->shader, vertexShader);
			glAttachShader(this->shader, fragmentShader);
			glLinkProgram(this->shader);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			glGenVertexArrays(1, &vertexArrayObject);
			glBindVertexArray(vertexArrayObject);
		}

		void SetPointSize(float newSize) const { glPointSize(newSize); }

		void DrawPoint() const {
			glBindVertexArray(vertexArrayObject);
			glUseProgram(this->shader);
			glDrawArrays(GL_POINTS, 0, 1);

		}

		void ClearData() {
			glDeleteProgram(shader);
			glDeleteVertexArrays(1, &vertexArrayObject);
		}

		~SinglePointShader() {

		}

	private:
		GLuint shader;
		GLuint vertexArrayObject;
	};

	class TriangleShader
	{
	public:
		TriangleShader() = default;

		TriangleShader(const GLchar* vertex, const GLchar* fragment) {

			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertex, NULL);
			glCompileShader(vertexShader);

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragment, NULL);
			glCompileShader(fragmentShader);

			this->shader = glCreateProgram();
			glAttachShader(this->shader, vertexShader);
			glAttachShader(this->shader, fragmentShader);
			glLinkProgram(this->shader);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			glGenVertexArrays(1, &vertexArrayObject);
			glBindVertexArray(vertexArrayObject);
		}

		void SetPointSize(float newSize) const { glPointSize(newSize); }

		void DrawPoint() const {
			glBindVertexArray(vertexArrayObject);
			glUseProgram(this->shader);
			glDrawArrays(GL_POINTS, 0, 1);

		}

		void ClearData() {
			glDeleteProgram(shader);
			glDeleteVertexArrays(1, &vertexArrayObject);
		}

		~TriangleShader() {

		}

	private:
		GLuint shader;
		GLuint vertexArrayObject;
	};
}