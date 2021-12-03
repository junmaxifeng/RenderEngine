#include "MeshBase.h"
#include "Camera.h"
#include "Texture2D.h"

MeshBase::MeshBase()
{
	//mType = NodeType::GEOMETRY;
}

MeshBase::~MeshBase()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(4, mVBO);
	glDeleteBuffers(1, &mEBO);
}

void MeshBase::setup()
{

	GLint oldVAO = -1;
	GLint oldVBO = -1;
	GLint oldEBO = -1;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVAO);
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldVBO);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldEBO);

	glGenVertexArrays(1, &mVAO);
	glGenBuffers(4, mVBO);
	glGenBuffers(1, &mEBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 3*mVertexAttributes.positions.size() * sizeof(GLdouble), mVertexAttributes.positions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 3*mVertexAttributes.normals.size() * sizeof(GLdouble), mVertexAttributes.normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 4*mVertexAttributes.colors.size() * sizeof(GLdouble), mVertexAttributes.colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO[3]);
	glBufferData(GL_ARRAY_BUFFER, 2 * mVertexAttributes.uvs.size() * sizeof(GLdouble), mVertexAttributes.uvs.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_DOUBLE, GL_FALSE, 2 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mVertexAttributes.indices.size() * sizeof(GLuint), mVertexAttributes.indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, oldVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldEBO);
	glBindVertexArray(oldVAO);
}

void MeshBase::draw(SceneSetting *setting)
{
	SceneNode::draw(setting);
	GLint oldVAO = -1;
	GLint oldVBO = -1;
	GLint oldEBO = -1;
	GLint oldProgram = -1;
	Shader *shader = getMaterial();
	shader->use();
	shader->setInt("_MainTex",0);
	static Texture *mainTex = new Texture2D("Resources/skybox.jpg");
	glActiveTexture(GL_TEXTURE0);
	mainTex->use();

	glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVAO);
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldVBO);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldEBO);
	//assert(mShader != nullptr);
	//mShader->setGeometryShaderPath("ShaderSources/Phong/geo.glsl");
	//mShader->InitProgram();
	//mShader->use();
	//setting->camera->setup(mShader);
	//mShader->setMat4("modelMatrix", mTransform);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glDrawElements(GL_PATCHES, mVertexAttributes.indices.size(), GL_UNSIGNED_INT, 0);
	//mShader->setGeometryShaderPath("ShaderSources/Phong/geo_normal.glsl");
	//mShader->InitProgram();
	//mShader->use();
	//setting->camera->setup(mShader);
	//mShader->setMat4("modelMatrix", mTransform);
	//glDrawElements(GL_PATCHES, mVertexAttributes.indices.size(), GL_UNSIGNED_INT, 0);
	////glDrawElements(GL_LINE_STRIP, mVertexAttributes.indices.size(), GL_UNSIGNED_INT, 0);
	////glDrawElements(GL_POINTS, mVertexAttributes.indices.size(), GL_UNSIGNED_INT, 0);
	glUseProgram(oldProgram);
	glBindBuffer(GL_ARRAY_BUFFER, oldVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldEBO);
	glBindVertexArray(oldVAO);
	mainTex->release();
}
