#pragma once
#include <list>
#include "Shader.h"
#include <glm/glm.hpp>


enum class NodeType:int
{
	DEFAULT,
	GEOMETRY
};
class Scene;
class Camera;
class LightBase;
class SkyBox;
class MeshBase;
struct SceneSetting
{
	SceneSetting():camera(nullptr),
	light(nullptr),
	skybox(nullptr)
	{
		
	}
	Camera *camera;
	LightBase *light;
	SkyBox *skybox;
};
class SceneNode
{
public:
	friend class Scene;
	SceneNode(const glm::mat4x4& transform= glm::mat4x4(1.0f));
	SceneNode(const SceneNode& other);
	SceneNode(SceneNode* parent);
	virtual ~SceneNode();
	void setParent(SceneNode* mParent);
	void appendChild(SceneNode* child);
	void setMaterial(Shader *shader);
	Shader* getMaterial();
	glm::mat4 getTransform();

	virtual void translation(const glm::vec3 &vec);
	virtual void rotate(const glm::vec3 &vec, const double angle);
	virtual void scale(const glm::vec3 &vec);
	//virtual void setMesh(MeshBase *mesh);
protected:
	virtual void draw(SceneSetting *setting);
	virtual NodeType getType();
protected:
	std::list<SceneNode*> mChildren;
	SceneNode* mParent;
	glm::mat4 mTransform;
	Shader *mShader;
	//MeshBase *mMesh;
	NodeType mType;
};

