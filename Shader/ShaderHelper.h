#pragma once
#include <glad/glad.h> 
#include "GLFW/glfw3.h"

namespace Shaders {
	namespace Helper {

		GLuint MakeShader(const GLchar* shaderSource, const GLuint shaderTypeId) {
			GLuint shader = glCreateShader(shaderTypeId);
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);

			return shader;
		}

		GLuint MakeVertexShader(const GLchar* vertexSource) {
			return MakeShader(vertexSource, GL_VERTEX_SHADER);
		}

		GLuint MakeTesselationControlShader(const GLchar* tesselationControlSource) {
			return MakeShader(tesselationControlSource, GL_TESS_CONTROL_SHADER);
		}

		GLuint MakeTesselationEvaluationShader(const GLchar* tesselationEvaluationSource) {
			return MakeShader(tesselationEvaluationSource, GL_TESS_EVALUATION_SHADER);
		}

		GLuint MakeGeometryShader(const GLchar* geometrySource){
			return MakeShader(geometrySource, GL_GEOMETRY_SHADER);
		}

		GLuint MakeFragmentShader(const GLchar* fragmentSource) {
			return MakeShader(fragmentSource, GL_FRAGMENT_SHADER);
		}
	}
}