#include "SceneNode.h"

#include "Camera.h"
#include "MeshBase.h"
#include "SkyBox.h"
#include "LightBase.h"

SceneNode::SceneNode(const glm::mat4 &tranform) :
	mParent(nullptr),
	mType(NodeType::DEFAULT),
	mTransform(tranform),
	mShader(nullptr)
	//mMesh(nullptr)
{

}

SceneNode::SceneNode(const SceneNode & other)
{
	mChildren = other.mChildren;
	mParent = other.mParent;
	mTransform = other.mTransform;
	mShader = other.mShader;
	//mMesh = other.mMesh;
	mType = other.mType;
}

SceneNode::SceneNode(SceneNode* parent) :
	mType(NodeType::DEFAULT),
	mTransform(1.0f),
	mShader(nullptr)
	//mMesh(nullptr)
{
	setParent(parent);
}


void SceneNode::setParent(SceneNode* parent)
{
	mParent = parent;
	parent->mChildren.push_back(this);
}

void SceneNode::appendChild(SceneNode* child)
{
	child->setParent(this);
}

SceneNode::~SceneNode()
{
	for (SceneNode *&child : mChildren)
	{
		delete child;
		child = nullptr;
	}
	if (mParent)
	{
		for (std::list<SceneNode*>::iterator i = mParent->mChildren.begin(); i != mParent->mChildren.end(); i++)
		{
			if (this == *i)
			{
				mParent->mChildren.erase(i);
			}
		}
	}
}

void SceneNode::draw(SceneSetting *setting)
{
	Shader *shader = getMaterial();
	glm::mat4 transform(1.0f);
	if (shader)
	{
		GLint oldProgram = -1;
		glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
		shader->use();

		if(setting->skybox)
		{
			setting->skybox->draw(setting);
			//setting->skybox->setup();
		}
		if (setting->light)
		{
			setting->light->setup(shader);
		}
		transform =getTransform();
		setting->camera->setup(shader);
		shader->setMat4("modelMatrix", transform);
		glUseProgram(oldProgram);
	}
	for (std::list<SceneNode*>::iterator i = mChildren.begin(); i != mChildren.end(); i++)
	{
		(*i)->draw(setting);
	}
}

NodeType SceneNode::getType()
{
	return mType;
}


void SceneNode::setMaterial(Shader *shader)
{
	mShader = shader;
}
Shader * SceneNode::getMaterial()
{
	if (mShader)
	{
		return mShader;
	}
	else if (mParent)
	{
		return mParent->getMaterial();
	}
	else
	{
		return nullptr;
	}
}
glm::mat4 SceneNode::getTransform()
{
	if (mParent)
	{
		return mParent->getTransform()*mTransform;
	}else
	{
		return mTransform;
	}
}
void SceneNode::translation(const glm::vec3 & vec)
{
	mTransform = glm::translate(mTransform, vec);
}
void SceneNode::rotate(const glm::vec3 & vec, const double angle)
{
	mTransform = glm::rotate(mTransform, static_cast<float>(angle),vec);
}
void SceneNode::scale(const glm::vec3 & vec)
{
	mTransform = glm::scale(mTransform, vec);
}
//
//void SceneNode::setMesh(MeshBase *mesh)
//{
//	mMesh = mesh;
//}
