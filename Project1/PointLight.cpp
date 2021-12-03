#include "PointLight.h"

void PointLight::setup(Shader * shader)
{
	shader->setVec3("lightSource[0].position",mPosition);
	shader->setVec3("lightSource[0].color", mColor);
}
