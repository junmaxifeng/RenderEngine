#include "Engine.h"
#include "Scene.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "ShaderFactory.h"

void Engine::init()
{
	initShaders();
}

Engine* Engine::GetEngineInstance()
{
	static Engine *engine = new Engine;
	return engine;
}

Scene * Engine::scene()
{
	return mScene;
}

Shader * Engine::getShader(const std::string & key)
{
	return mShaderManager->getShader(key);
}

Engine::Engine()
{
	mShaderManager = ShaderManager::GetInstance();
	mScene = new Scene;
	init();
}

Engine::~Engine()
{

}


void Engine::initShaders() const 
{
	mShaderManager->appendEntry("default", ShaderFactory::GetDefaultShader());
	mShaderManager->appendEntry("displayNormal", ShaderFactory::GetNormalDisplayShader());
	mShaderManager->appendEntry("skyBox", ShaderFactory::GetSkyBoxShader());
}