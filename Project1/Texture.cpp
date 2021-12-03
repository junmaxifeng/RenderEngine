#include "Texture.h"

Texture::Texture() :
	mTexId(0),
mLastTexId(0)
{

}

Texture::Texture(const std::string & path):
	mTexId(0),
	mLastTexId(0)
{
	setPath(path);
}

Texture::~Texture()
{
	if(mTexId!=0)
	{
		glDeleteTextures(1,&mTexId);
	}
}

void Texture::setPath(const std::string & path)
{
	mImgPath = path;
}

void Texture::setup()
{

}

void Texture::use()
{
}

void Texture::release()
{
}

GLuint Texture::getID()
{
	return GLuint();
}
