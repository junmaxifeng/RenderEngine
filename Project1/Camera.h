#pragma once
#include "Scene.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum class CameraType :unsigned int
{
	NONE,
	PERSPECTIVE,
	ORTHO
};

class Camera :public SceneNode
{
public:
	friend class Scene;
	Camera() :
		mRootScene(nullptr),
		mType(CameraType::NONE),
		mViewMatrix(1.0f),
		mProjectionMatrix(1.0f)
	{

	}
	Camera(Scene* root) :
		mRootScene(root),
		mType(CameraType::NONE),
		mViewMatrix(1.0f),
		mProjectionMatrix(1.0f)
	{
		root->mCamera = this;
	}
	void setRootScene(Scene *root)
	{
		mRootScene = root;
	}
	void renderScene()
	{
		mRootScene->draw();
	}
	void setup(Shader *shader)
	{
		shader->setMat4("viewMatrix", mViewMatrix);
		shader->setMat4("projectionMatrix", mProjectionMatrix);
	}
	void lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up)
	{
		mPosition = eye;
		mForwardVec = center - eye;
		mUpVec = up;
		mRightVec = glm::cross(mForwardVec, mUpVec);
		mViewMatrix = glm::lookAt(eye, center, up);
	}
	void perspective(const double& fov, const double& aspect, const double& near, const double& far)
	{
		mType = CameraType::PERSPECTIVE;
		mFov = fov;
		mAspect = aspect;
		mNear = near;
		mFar = far;
		mProjectionMatrix = glm::perspective(fov, aspect, near, far);
	}
	void ortho(const double& left, const double& right, const double& bottom, const double& up, const double near, const double far)
	{
		mType = CameraType::ORTHO;
		mProjectionMatrix = glm::ortho(left, right, bottom, up, near, far);
	}

	virtual void translation(const glm::vec3 & vec) override
	{
		glm::vec3 target = mPosition + mForwardVec;
		mPosition = mPosition + vec;
		mViewMatrix = glm::lookAt(mPosition, mForwardVec + mPosition, mUpVec);
	}

	virtual void rotate(const glm::vec3 & vec, const double angle) override
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), static_cast<float>(angle), vec);

		mForwardVec = rotation * glm::vec4(mForwardVec, 0.0f);
		mRightVec = rotation * glm::vec4(mRightVec, 0.0f);
		mUpVec = rotation * glm::vec4(mUpVec, 0.0f);

		mViewMatrix = glm::lookAt(mPosition, mForwardVec + mPosition, mUpVec);
	}

	void rotateRoundTarget(const glm::vec3 & vec, const double angle)
	{
		glm::vec3 target = mPosition + mForwardVec;
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), static_cast<float>(angle), vec);
		mForwardVec = -rotation * glm::vec4(-mForwardVec, 0.0f);
		mUpVec = rotation * glm::vec4(mUpVec, 0.0f);
		mPosition = target - mForwardVec;

		mViewMatrix = glm::lookAt(mPosition, mForwardVec + mPosition, mUpVec);
	}

	virtual void scale(const glm::vec3 & vec) override
	{
		mTransform = glm::scale(mTransform, vec);
	}

	CameraType type()
	{
		return mType;
	}
	double fov()
	{
		return mFov;
	}
	double aspect()
	{
		return mAspect;
	}
	double near()
	{
		return mNear;
	}
	double far()
	{
		return mFar;
	}

	glm::vec3 position() {
		return mPosition;
	}
	glm::mat4 viewMatrix() {
		return mViewMatrix;
	}
	glm::mat4 projectionMatrix() {
		return mProjectionMatrix;
	}

	glm::vec3 forwardVec(){
		return mForwardVec;
	}
	glm::vec3 rightVec() {
		return mRightVec;
	}
	glm::vec3 upVec() {
		return mUpVec;
	}

protected:
private:
	CameraType mType;
	Scene* mRootScene;

	glm::vec3 mPosition;

	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;

	glm::vec3 mForwardVec;
	glm::vec3 mRightVec;
	glm::vec3 mUpVec;

	double mFov;
	double mAspect;
	double mNear;
	double mFar;
};

