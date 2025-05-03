#pragma once

#include <glad/glad.h> 
#include "GLFW/glfw3.h"
#include "ShaderHelper.h"
#include "ShaderRenderer.h"
#include <vector>

namespace Shaders {
	class Shader {
	public:
		virtual void Draw() const = 0;
		virtual void Draw(GLfloat positionOffset[]) const = 0;
		virtual void Draw(GLfloat positionOffset[], GLfloat color[]) const = 0;
		virtual void TesselateDraw() const = 0;
		void ClearData() const{
			glDeleteProgram(shader);
			glDeleteVertexArrays(1, &vertexArrayObject);
		}
	protected:
		void BindVAO() {
			glGenVertexArrays(1, &vertexArrayObject);
			glBindVertexArray(vertexArrayObject);
		};
	protected:
		GLuint shader;
		GLuint vertexArrayObject;
	};

	class SinglePointShader : public Shader
	{
	public:
		SinglePointShader() = default;

		SinglePointShader(const GLchar* vertex, const GLchar* fragment) {

			std::vector<GLuint> shaders;
			shaders.push_back(Helper::MakeVertexShader(vertex));
			shaders.push_back(Helper::MakeFragmentShader(fragment));

			this->shader = glCreateProgram();

			for (const auto& sh : shaders)
				glAttachShader(this->shader, sh);

			glLinkProgram(this->shader);

			for (const auto& sh : shaders)
				glDeleteShader(sh);

			shaders.clear();

			BindVAO();
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

			std::vector<GLuint> shaders;
			shaders.push_back(Helper::MakeVertexShader(vertex));
			shaders.push_back(Helper::MakeFragmentShader(fragment));

			this->shader = glCreateProgram();

			for (const auto& sh : shaders)
				glAttachShader(this->shader, sh);

			glLinkProgram(this->shader);

			for (const auto& sh : shaders)
				glDeleteShader(sh);

			shaders.clear();

			BindVAO();
		}

		TriangleShader(const GLchar* vertex, const GLchar* tesselationControl, const GLchar* tesselationEvaluation, const GLchar* fragment) {

			std::vector<GLuint> shaders;
			shaders.push_back(Helper::MakeVertexShader(vertex));
			shaders.push_back(Helper::MakeTesselationControlShader(tesselationControl));
			shaders.push_back(Helper::MakeTesselationEvaluationShader(tesselationEvaluation));
			shaders.push_back(Helper::MakeFragmentShader(fragment));

			this->shader = glCreateProgram();

			for (const auto& sh : shaders)
				glAttachShader(this->shader, sh);

			glLinkProgram(this->shader);

			for (const auto& sh : shaders)
				glDeleteShader(sh);

			shaders.clear();

			BindVAO();
		}


		TriangleShader(const GLchar* vertex, const GLchar* tesselationControl, const GLchar* tesselationEvaluation, const GLchar* geometry, const GLchar* fragment) {
			std::vector<GLuint> shaders;
			shaders.push_back(Helper::MakeVertexShader(vertex));
			shaders.push_back(Helper::MakeTesselationControlShader(tesselationControl));
			shaders.push_back(Helper::MakeTesselationEvaluationShader(tesselationEvaluation));
			shaders.push_back(Helper::MakeGeometryShader(geometry));
			shaders.push_back(Helper::MakeFragmentShader(fragment));

			this->shader = glCreateProgram();

			for (const auto& sh : shaders)
				glAttachShader(this->shader, sh);
			
			glLinkProgram(this->shader);

			for (const auto& sh : shaders)
				glDeleteShader(sh);

			shaders.clear();

			BindVAO();
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
			glPointSize(5.0);
			glDrawArrays(GL_PATCHES, 0, 3);
		}

		~TriangleShader() {

		}

	};
}