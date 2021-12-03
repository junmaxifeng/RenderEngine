#pragma once
#include "SceneNode.h"
#include "Texture2D.h"

class SkyBox :public SceneNode
{
public:
	SkyBox(const std::string &path);
	virtual ~SkyBox();
	void setup();
	virtual void draw(SceneSetting* setting) override;
protected:
private:
	uint32_t mIndices[6];
	Texture2D *mSkyBoxTex;
	Shader *mShader;
	GLuint mVAO, mVBO, mEBO;
};

