#include "pch.h"
#include "ShaderData.h"




std::string ShaderInterface::GenerateGLSL() const
{
    std::string formattedShaderSource;

    formattedShaderSource.append(StartInterface());
    for (const auto& f : fields)
        formattedShaderSource.append(std::format("{};\n", f.GenerateGLSL()));
    formattedShaderSource.append(EndInterface());

    return formattedShaderSource;
}

std::string ShaderInterface::StartInterface() const
{
    return std::format("{} {}{{ \n", io == input ? "in" : "out", interfaceType);
}

std::string ShaderInterface::EndInterface() const
{
    return std::format("}}{};\n", interfaceName);
}
