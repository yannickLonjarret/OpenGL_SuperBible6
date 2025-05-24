#pragma once
#include <vector>
#include <string>
#include "ShaderData.h"
#include <format>

class ShaderSourceGenerator
{
public:
	ShaderSourceGenerator(const std::vector<std::shared_ptr<ShaderData>>& data) : shaderInfo(data) {
		Generate();
	}

	const char* GetGLSL() const {
		return shaderSource.c_str();
	}

private:
	void Generate() {
		StartShader();
		FormatShaderSourceBody();
		EndShader();
	}

	void StartShader() {
		shaderSource.append("#version 460 core\n");
	}

	void FormatShaderSourceBody() {
		for (const auto& data : shaderInfo)
			shaderSource.append(std::format("{};\n", data->GenerateGLSL()));
	}

	void EndShader() {
		shaderSource.append("}\n\0");
	}
private:
	std::vector<std::shared_ptr<ShaderData>> shaderInfo;
	std::string shaderSource;
};

