#pragma once
#include "SceneNode.h"
//#include "Camera.h"
class Camera;
class LightBase;
class SkyBox;
class Scene
{
public:
	friend class Camera;
	Scene();
	virtual ~Scene();
	void setCamera(Camera *camera);
	void setLight(LightBase *light);
	void setSkyBox(SkyBox *skybox);
	void appendChild(SceneNode *);
protected:
	void draw();
private:
	SceneNode *mRootNode;
	Camera *mCamera;
	LightBase *mLight;
	SkyBox *mSkyBox;
};

