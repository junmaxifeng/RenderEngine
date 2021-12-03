#include "Vector4d.h"

Vector4d::Vector4d(const double &x,
	const double &y,
	const double &z,
	const double &w)
{
	mData.resize(4);
	mData[0] = x;
	mData[1] = y;
	mData[2] = z;
	mData[3] = w;
}

double& Vector4d::operator[](const uint32_t &index)
{
	return mData[index];
}