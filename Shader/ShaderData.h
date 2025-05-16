#pragma once
#include <string>
#include <format>
#include <vector>

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

class GLSLVariable : ShaderData {
public:
	GLSLVariable() {};
	GLSLVariable(const std::string& type, const std::string& name) :
		type(type), name(name) {}

	virtual std::string GenerateGLSL() const override {
		return std::format("{} {}", type, name);
	}

protected:
	std::string type;
	std::string name;
};

class GLSLArray: GLSLVariable {
public:
	std::string GenerateGLSL() const override {
		return std::format("{} {}[]", type, name);
	}
};

class ShaderVariable : public ShaderData {
public: 
	ShaderVariable() {};

	ShaderVariable(const IOType ioData, const std::string& type, const std::string& name) : 
		io(ioData){
		variableData = GLSLVariable(type, name);
	}

	std::string GenerateGLSL() const override{
		return std::format("{} {}", io == input ? "in" : "out", variableData.GenerateGLSL());
	}
private:
	IOType io;
	GLSLVariable variableData;
};

class ShaderLayout : public ShaderData {
	ShaderLayout(const int data, const ShaderVariable& var, const std::string& specifier = "location") :
		layoutSpecifier(specifier), specifierData(data), variable(var){}

	ShaderLayout(const int position, const IOType ioData, const std::string& type, const std::string& name, const std::string& specifier = "location") :
		layoutSpecifier(specifier), specifierData(position) {
		variable = ShaderVariable(ioData, type, name);
	}

	std::string GenerateGLSL() const override {
		return std::format("layout ({} = {}) {};\n", layoutSpecifier, specifierData, variable.GenerateGLSL());
	}
private:
	ShaderVariable variable;
	std::string layoutSpecifier;
	int specifierData;
};


class ShaderInterface : public ShaderData {
public:
	ShaderInterface() {};

	ShaderInterface(const IOType ioData, const std::vector<GLSLVariable>& fields, const std::string& name, const std::string& type) :
		io(ioData), fields(fields), interfaceName(name) {}

	std::string GenerateGLSL() const override;
private:
	std::string StartInterface() const;
	std::string EndInterface() const;
private:
	IOType io;
	std::vector<GLSLVariable> fields;
	std::string interfaceName;
	std::string interfaceType;
};



