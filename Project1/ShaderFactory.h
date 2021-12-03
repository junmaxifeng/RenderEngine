#pragma once
#include "EngineClasses.h"
class ShaderFactory
{
public:
	static Shader* GetDefaultShader();
	static Shader* GetNormalDisplayShader();
	static Shader* GetSkyBoxShader();
protected:
private:
};

