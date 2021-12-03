#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
}

ShaderManager * ShaderManager::GetInstance()
{
	static ShaderManager* gShaderManager = new ShaderManager();
	return gShaderManager;
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::appendEntry(std::string key, Shader* shader)
{
	mShaderMap.insert(std::pair<std::string,Shader*>{key, shader});
}

Shader * ShaderManager::getShader(const std::string & key)
{
	return mShaderMap[key];
}
