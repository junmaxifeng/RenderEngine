#pragma once
#include "Texture.h"
class Texture2D:public Texture
{
public:
	Texture2D();
	Texture2D(const std::string &path);
	virtual void setup() override;
	virtual void use() override;
	virtual void release() override;
protected:
private:
};

