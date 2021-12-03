#ifndef LIGHTBASE_H
#define LIGHTBASE_H
#include "Shader.h"
class LightBase
{
public:
	LightBase();
	virtual ~LightBase();
	virtual void setup(Shader *shader)=0;
protected:
private:
};

#endif

