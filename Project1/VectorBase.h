#pragma once
#ifndef VECTORBASE
#define VECTORBASE
#include <vector>
template<class Type>
class VectorBase
{
public:
	Type length()
	{
		Type len = 0;
		for (Type element : mData)
		{
			len += mData * mData;
		}
		return sqrt(len);
	}
	const VectorBase<Type>& operator=(const VectorBase<Type>& other)
	{
		mData.resize(other.mData.size());
		for (const uint32_t index=0;index<other.mData.size();index++)
		{
			mData[index] = other.mData.at(index);
		}
	}
protected:
	std::vector<Type> mData;
};
#endif

