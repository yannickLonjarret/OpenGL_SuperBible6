#pragma once
#include <vector>
#include <string>
#include "ShaderData.h"

class ShaderSourceGenerator
{
public:
	ShaderSourceGenerator(const std::vector<std::shared_ptr<ShaderData>>& data) : shaderInfo(data) {
		Generate();
	}


private:
	void Generate() {
		StartShader();
		FormatShaderSourceBody();
		EndShader();
	}

	void StartShader() {
		shaderSource.push_back("#version 460 core\n");
	}

	void FormatShaderSourceBody() {
		for (const auto& data : shaderInfo)
			shaderSource.emplace_back(data->GenerateGLSL());
	}

	void EndShader() {
		shaderSource.push_back("}\n\0");
	}
private:
	std::vector<std::shared_ptr<ShaderData>> shaderInfo;
	std::vector<std::string> shaderSource;
};

