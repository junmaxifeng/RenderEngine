#ifndef MESHBASE_H
#define MESHBASE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glad/glad.h>
//#include "Shader.h"
#include "Scene.h"

enum class MeshType
{
	Sphere,
};

struct VertexAttributes
{
	std::vector<glm::dvec3> positions;
	std::vector<glm::dvec3> normals;
	std::vector<glm::dvec4> colors;
	std::vector<glm::dvec2> uvs;
	std::vector<glm::uint> indices;
};

class MeshBase:public SceneNode
{
public:
	MeshBase();
	virtual ~MeshBase();
	virtual void draw(SceneSetting *setting=nullptr);
	void setup();
protected:
	VertexAttributes mVertexAttributes;
private:
	GLuint mVAO;
	GLuint mVBO[4];
	GLuint mEBO;
};
#endif


