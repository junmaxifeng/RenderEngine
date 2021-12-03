#include "Scene.h"
#include "Camera.h"

Scene::Scene() :
	mRootNode(new SceneNode),
	mCamera(nullptr),
	mLight(nullptr),
	mSkyBox(nullptr)
{

}

Scene::~Scene()
{
	delete mRootNode;
	mRootNode = nullptr;
}

void Scene::setCamera(Camera *camera)
{
	mCamera = camera;
	camera->mRootScene = this;
}

void Scene::setLight(LightBase * light)
{
	mLight = light;
}

void Scene::setSkyBox(SkyBox * skybox)
{
	mSkyBox = skybox;
}

void Scene::appendChild(SceneNode *child)
{
	mRootNode->appendChild(child);
}

void Scene::draw()
{
	SceneSetting setting;
	setting.camera = mCamera;
	setting.light = mLight;
	setting.skybox = mSkyBox;
	mRootNode->draw(&setting);
}