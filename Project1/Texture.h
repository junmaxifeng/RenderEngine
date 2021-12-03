#ifndef  TEXTURE_H
#define TEXTURE_H
#include "SceneNode.h"
#include <string>
#include <glad/glad.h>


class Texture :public SceneNode
{

public:
	Texture();
	Texture(const std::string &path);
	virtual ~Texture();
	void setPath(const std::string &path);
	virtual void setup();

	virtual void use();
	virtual void release();

	GLuint getID();
protected:
	std::string mImgPath;
	GLuint mTexId;
	GLuint mLastTexId;

};
#endif

