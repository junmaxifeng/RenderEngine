#include "SkyBox.h"

#include "Camera.h"
#include "Math.h"
#include "ShaderFactory.h"
#include "ShaderManager.h"
#include "glm/gtc/matrix_inverse.hpp"


SkyBox::SkyBox(const std::string &path) :
	mIndices{ 0,1,3,2,3,1 },
	mSkyBoxTex(nullptr),
	mShader(nullptr)
{
	mShader = ShaderFactory::GetSkyBoxShader();
	mSkyBoxTex = new Texture2D(path);
	setup();
}

SkyBox::~SkyBox()
{
	if (mSkyBoxTex)
		delete mSkyBoxTex;
	mSkyBoxTex = nullptr;
	if (mShader)
		delete mShader;
	mShader = nullptr;
	if (mVAO != 0)
		glDeleteVertexArrays(1, &mVAO);
	if (mVBO != 0)
		glDeleteBuffers(1, &mVBO);
	if (mEBO != 0)
		glDeleteBuffers(1, &mEBO);
}

void SkyBox::setup()
{
	double vertices[]={
		-1.0,-1.0,0.0,0.0,
		+1.0,-1.0,1.0,0.0,
		+1.0,+1.0,1.0,1.0,
		-1.0,+1.0,0.0,1.0
	};

	GLint oldVAO = -1;
	GLint oldVBO = -1;
	GLint oldEBO = -1;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVAO);
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldVBO);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldEBO);

	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)(sizeof(double)*2));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, oldVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldEBO);
	glBindVertexArray(oldVAO);
}

void SkyBox::draw(SceneSetting * setting)
{
	Camera *camera = setting->camera;
	double fovy = camera->fov();
	glm::vec3 forward = camera->forwardVec();
	glm::vec3 right = camera->rightVec();
	glm::vec3 up = camera->upVec();

	glm::vec4 v0(-tan(fovy / 2)*camera->aspect(), -tan(fovy / 2), 1.0, 0.0);
	glm::vec4 v1(-v0.x, +v0.y, v0.z, 0.0);
	glm::vec4 v2(-v0.x, -v0.y, v0.z, 0.0);
	glm::vec4 v3(+v0.x, -v0.y, v0.z, 0.0);


	v0 = (camera->viewMatrix())*v0;
	v1 = (camera->viewMatrix())*v1;
	v2 = (camera->viewMatrix())*v2;
	v3 = (camera->viewMatrix())*v3;




	//double vertices[] = {
	//	-1.0,-1.0,0.0,0.0,
	//	+1.0,-1.0,1.0,0.0,
	//	+1.0,+1.0,1.0,1.0,
	//	-1.0,+1.0,0.0,1.0
	//};
	double vertices[] = {
		-1.0,-1.0,v0.x,v0.y,v0.z,
		+1.0,-1.0,v1.x,v1.y,v1.z,
		+1.0,+1.0,v2.x,v2.y,v2.z,
		-1.0,+1.0,v3.x,v3.y,v3.z
	};

	GLint oldVAO = -1;
	GLint oldVBO = -1;
	GLint oldEBO = -1;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVAO);
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldVBO);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldEBO);

	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(sizeof(double) * 2));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, oldVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldEBO);
	glBindVertexArray(oldVAO);

	////SceneNode::draw(setting);
	//GLint oldVAO = -1;
	//GLint oldVBO = -1;
	//GLint oldEBO = -1;
	GLint oldProgram = -1;
	glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVAO);
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldVBO);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldEBO);


	mShader->use();
	mShader->setInt("_MainTex", 0);
	glActiveTexture(GL_TEXTURE0);
	mSkyBoxTex->use();


	glBindVertexArray(mVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUseProgram(oldProgram);
	glBindBuffer(GL_ARRAY_BUFFER, oldVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldEBO);
	glBindVertexArray(oldVAO);
	mSkyBoxTex->release();
}
