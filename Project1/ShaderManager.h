#ifndef ShaderManager_H
#define  ShaderManager_H
#include <unordered_map>
class Shader;
class ShaderManager
{
public:
	static ShaderManager* GetInstance();
	virtual ~ShaderManager();
	void appendEntry(std::string key,Shader *shader);
	Shader *getShader(const std::string &key);
protected:
private:
	ShaderManager();
	std::unordered_map<std::string, Shader*> mShaderMap;
};
#endif

