#pragma once
#include <string>
#include <format>
class ShaderData
{
public:
	virtual std::string GenerateGLSL() const = 0;
};

enum IOType
{
	input = 0,
	output = 1
};

class ShaderVariable : public ShaderData {
public: 
	ShaderVariable() {};

	ShaderVariable(const IOType ioData, const std::string& type, const std::string& name) : 
		io(ioData), type(type), name(name){}

	std::string GenerateGLSL() const{
		return std::format("{} {} {}", io == input ? "in" : "out", type, name);
	}
private:
	IOType io;
	std::string type;
	std::string name;
};

class ShaderLayout : public ShaderData {
	ShaderLayout(const std::string& specifier = "location", const int data, const ShaderVariable& var) :
		layoutSpecifier(specifier), specifierData(data), variable(var){}

	ShaderLayout(const std::string& specifier = "location", const int position, const IOType ioData, const std::string& type, const std::string& name) :
		layoutSpecifier(specifier), specifierData(position) {
		variable = ShaderVariable(ioData, type, name);
	}

	std::string GenerateGLSL() const {
		return std::format("layout ({} = {}) {}\n", layoutSpecifier, specifierData, variable.GenerateGLSL());
	}
private:
	ShaderVariable variable;
	std::string layoutSpecifier;
	int specifierData;
};



