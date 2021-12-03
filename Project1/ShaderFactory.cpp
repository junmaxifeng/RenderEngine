#include "ShaderFactory.h"
#include "Shader.h"

Shader * ShaderFactory::GetDefaultShader()
{
	static Shader *shader = new Shader;
	shader->setVertexShaderPath("ShaderSources/Phong/vert.glsl");
	shader->setTessConShaderPath("ShaderSources/Phong/tess_con.glsl");
	shader->setTessEvalShaderPath("ShaderSources/Phong/tess_eval.glsl");
	shader->setGeometryShaderPath("ShaderSources/Phong/geo.glsl");
	shader->setFragShaderPath("ShaderSources/Phong/frag.glsl");
	shader->InitProgram();
	return shader;
}

Shader * ShaderFactory::GetNormalDisplayShader()
{
	static Shader *shader = new Shader;
	shader->setVertexShaderPath("ShaderSources/Phong/vert.glsl");
	shader->setTessConShaderPath("ShaderSources/Phong/tess_con.glsl");
	shader->setTessEvalShaderPath("ShaderSources/Phong/tess_eval.glsl");
	shader->setGeometryShaderPath("ShaderSources/Phong/geo_normal.glsl");
	shader->setFragShaderPath("ShaderSources/Phong/frag.glsl");
	shader->InitProgram();
	return shader;
}

Shader * ShaderFactory::GetSkyBoxShader()
{
	static Shader *shader = new Shader;
	shader->setVertexShaderPath("ShaderSources/SkyBox/vert.glsl");
	shader->setFragShaderPath("ShaderSources/SkyBox/frag.glsl");
	shader->InitProgram();
	return shader;
}
