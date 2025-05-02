#pragma once

#include <glad/glad.h> 
#include "GLFW/glfw3.h"

namespace Shaders {
	class Shader {
	public:
		virtual void Draw() const = 0;
		virtual void Draw(GLfloat positionOffset[]) const = 0;
		virtual void Draw(GLfloat positionOffset[], GLfloat color[]) const = 0;
		virtual void TesselateDraw() const = 0;
		void ClearData() {
			glDeleteProgram(shader);
			glDeleteVertexArrays(1, &vertexArrayObject);
		}
	protected:
		GLuint shader;
		GLuint vertexArrayObject;
	};

	class SinglePointShader : public Shader
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

		void Draw() const override {
			glUseProgram(this->shader);
			glDrawArrays(GL_POINTS, 0, 1);
		}

		void Draw(GLfloat positionOffset[]) const override {
			glUseProgram(this->shader);
			glVertexAttrib4fv(0, positionOffset);
			glDrawArrays(GL_POINTS, 0, 1);
		}

		void Draw(GLfloat positionOffset[], GLfloat color[]) const override {
			glUseProgram(this->shader);
			glVertexAttrib4fv(0, positionOffset);
			glVertexAttrib4fv(1, color);
			glDrawArrays(GL_POINTS, 0, 1);

		}

		void TesselateDraw() const override {
			
		}

		~SinglePointShader() {

		}
	};

	class TriangleShader : public Shader
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

		TriangleShader(const GLchar* vertex, const GLchar* tesselationControl, const GLchar* tesselationEvaluation, const GLchar* fragment) {

			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertex, NULL);
			glCompileShader(vertexShader);

			GLuint tesselationControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
			glShaderSource(tesselationControlShader, 1, &tesselationControl, NULL);
			glCompileShader(tesselationControlShader);

			GLuint tesselationEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
			glShaderSource(tesselationEvaluationShader, 1, &tesselationEvaluation, NULL);
			glCompileShader(tesselationEvaluationShader);

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragment, NULL);
			glCompileShader(fragmentShader);

			this->shader = glCreateProgram();
			glAttachShader(this->shader, vertexShader);
			glAttachShader(this->shader, tesselationControlShader);
			glAttachShader(this->shader, tesselationEvaluationShader);
			glAttachShader(this->shader, fragmentShader);
			glLinkProgram(this->shader);

			glDeleteShader(vertexShader);
			glDeleteShader(tesselationControlShader);
			glDeleteShader(tesselationEvaluationShader);
			glDeleteShader(fragmentShader);

			glGenVertexArrays(1, &vertexArrayObject);
			glBindVertexArray(vertexArrayObject);
		}

		void SetPointSize(float newSize) const { glPointSize(newSize); }

		void Draw() const override {
			glUseProgram(this->shader);

			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		void Draw(GLfloat positionOffset[]) const override {
			glUseProgram(this->shader);
			glVertexAttrib4fv(0, positionOffset);
			glDrawArrays(GL_TRIANGLES, 0, 3);

		}

		void Draw(GLfloat positionOffset[], GLfloat color[]) const override {
			glUseProgram(this->shader);
			glVertexAttrib4fv(0, positionOffset);
			glVertexAttrib4fv(1, color);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		void TesselateDraw() const override {
			glUseProgram(this->shader);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawArrays(GL_PATCHES, 0, 3);
		}

		~TriangleShader() {

		}

	};
}