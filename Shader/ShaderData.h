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

class ShaderOperation : ShaderData {
public:
	std::string GenerateGLSL() const override final { return operationResult; }
protected: 
	std::string operationResult;
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

	std::string GetName() const { return name; }
protected:
	std::string type;
	std::string name;
};

class GLSLArray: public GLSLVariable {
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
	std::string GetName() const { return interfaceName; }
private:
	std::string StartInterface() const;
	std::string EndInterface() const;
private:
	IOType io;
	std::vector<GLSLVariable> fields;
	std::string interfaceName;
	std::string interfaceType;
};

class ShaderAssign : public ShaderOperation {
public:
	ShaderAssign(GLSLVariable& assign, GLSLVariable& read) {
		operationResult = std::format("{} = {}", assign.GetName(), read.GetName());
	};

	ShaderAssign(GLSLVariable& assign, ShaderAssign& read) {
		operationResult = std::format("{} = {}", assign.GetName(), read.operationResult);
	};

	ShaderAssign(GLSLArray& assign, std::string& arrayAccessor, GLSLVariable& read) {
		operationResult = std::format("{}[{}] = {}", assign.GetName(), arrayAccessor, read.GetName());
	};

	ShaderAssign(GLSLVariable& assign, GLSLVariable& read, std::string& arrayAccessor) {
		operationResult = std::format("{} = {}[{}]", assign.GetName(), read.GetName(), arrayAccessor);
	};

	ShaderAssign(ShaderInterface& assign, GLSLVariable& access, GLSLVariable& read) {
		operationResult = std::format("{}.{} = {}", assign.GetName(), access.GetName(), read);
	};

	ShaderAssign(GLSLVariable& assign, GLSLVariable& read, GLSLVariable& access) {
		operationResult = std::format("{} = {}.{}", assign.GetName(), access.GetName(), read);
	};
};

class ShaderAdd : public ShaderOperation {
public:
	ShaderAdd(GLSLVariable& assign, GLSLVariable& read) {
		operationResult = std::format("{} + {}", assign.GetName(), read.GetName());
	};

	ShaderAdd(GLSLVariable& assign, GLSLVariable& read, std::string& arrayAccessor) {
		operationResult = std::format("{} + {}[{}]", assign.GetName(), read.GetName(), arrayAccessor);
	};

	ShaderAssign(ShaderInterface& assign, GLSLVariable& access, GLSLVariable& read) {
		operationResult = std::format("{}.{} + {}", assign.GetName(), access.GetName(), read);
	};
};



