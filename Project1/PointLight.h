#pragma once
#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "LightBase.h"
#include <glm/glm.hpp>

class PointLight:public LightBase
{
public:
	virtual void setup(Shader* shader) override;
protected:
private:
	glm::vec3 mPosition;
	glm::vec3 mColor;
};
#endif


