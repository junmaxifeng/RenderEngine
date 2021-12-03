#ifndef ENGINE_H
#define ENGINE_H
#include <string>

#include "EngineClasses.h"
class Engine
{
public:
	virtual ~Engine();
	void init();
	static Engine* GetEngineInstance();
	Scene *scene();

	Shader *getShader(const std::string &key);
protected:
private:
	Engine();
	void initShaders() const;

private:
	ShaderManager *mShaderManager;
	Scene *mScene;
};
#endif


