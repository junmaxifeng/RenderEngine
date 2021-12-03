#pragma once
#include "VectorBase.h"
class Vector4d : public VectorBase<double>
{
public:
	Vector4d(const double &x,
		const double &y, 
		const double &z, 
		const double &w);
	double& operator[](const uint32_t &index);
};

