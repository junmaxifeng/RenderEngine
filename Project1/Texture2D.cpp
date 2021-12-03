#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D():Texture()
{
}

Texture2D::Texture2D(const std::string & path):Texture(path)
{
	Texture2D::setup();
}

void Texture2D::setup()
{
	GLint oldTex = -1;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTex);
	glGenTextures(1, &mTexId);
	glBindTexture(GL_TEXTURE_2D, mTexId);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(mImgPath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "texture failed to load at path: " << mImgPath.c_str() << std::endl;
		stbi_image_free(data);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, oldTex);
}

void Texture2D::use()
{
	glGetIntegerv(GL_TEXTURE_BINDING_2D, reinterpret_cast<GLint*>(&mLastTexId));
	glBindTexture(GL_TEXTURE_2D, mTexId);
}

void Texture2D::release()
{
	glBindTexture(GL_TEXTURE_2D, mLastTexId);
}