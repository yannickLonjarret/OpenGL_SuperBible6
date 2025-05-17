#pragma once
#include <string>
#include <format>
#include <vector>
#include <ranges>

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

class ShaderLayoutArgument : public ShaderData {
public:
	ShaderLayoutArgument(const std::string& qual = "location", const int data = -1) : qualifier(qual), value(data) {};

	std::string GenerateGLSL() const override {
		return value > 0 ? std::format("{} = {}", qualifier, value) : std::format("{}", qualifier);
	}
private:
	std::string qualifier;
	int value;

};

class ShaderLayout : public ShaderData {
	ShaderLayout(const std::vector<ShaderLayoutArgument>& args, const ShaderVariable& var) :
		args(args), variable(var) {}

	std::string GenerateGLSL() const override {
		std::string formattedArs;
		for (const auto& arg : std::ranges::drop_view{ args,1 })
			formattedArs.append(std::format(",{}", arg.GenerateGLSL()));

		return std::format("layout ({}) {};\n", formattedArs, variable.GenerateGLSL());
	}
private:
	ShaderVariable variable;
	std::vector<ShaderLayoutArgument> args;
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



