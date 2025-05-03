#pragma once
#include <vector>
#include <string>

class ShaderSourceGenerator
{
public:

private:
	void StartShader() {
		shaderSource.push_back("#version 460 core\n");
	}

	void EndShader() {
		shaderSource.push_back("}\n\0");
	}
private:
	std::vector<std::string> shaderSource;
};

