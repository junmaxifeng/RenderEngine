#pragma once
#include "MeshBase.h"
#include "EngineClasses.h"
class Sphere :
	public MeshBase
{
public:
	Sphere(const glm::dvec3 &centre, const double &radius,const glm::uint &longitudePrecision=10,const glm::uint &latitudePrecision=10);
	static SceneNode* getASphereNode(const glm::dvec3 &centre, const double &radius, const glm::uint &longitudePrecision = 10, const glm::uint &latitudePrecision = 10);
protected:
private:
	glm::dvec3 mCentre;
	double mRadius;
	glm::uint mLongitudePrecision;
	glm::uint mLatitudePrecision;
};

