#include "Sphere.h"
#include "Math.h"


Sphere::Sphere(const glm::dvec3 &centre, const double &radius, const glm::uint &longitudePrecision, const glm::uint &latitudePrecision) :
	mCentre(centre),
	mRadius(radius),
	mLongitudePrecision(longitudePrecision),
	mLatitudePrecision(latitudePrecision)
{
	std::vector<double> phiArray = Math::linspace(0,  2*Math::PI, mLongitudePrecision);
	//phiArray.erase(phiArray.end() - 1);
	std::vector<double> thetaArray = Math::linspace(-Math::PI / 2, Math::PI / 2, mLatitudePrecision);
	mVertexAttributes.positions.resize(mLongitudePrecision*mLatitudePrecision);
	mVertexAttributes.normals.resize(mLongitudePrecision*mLatitudePrecision);
	mVertexAttributes.colors.resize(mLongitudePrecision*mLatitudePrecision);
	mVertexAttributes.uvs.resize(mLongitudePrecision*mLatitudePrecision);
	mVertexAttributes.indices.resize((mLatitudePrecision - 1)*(mLongitudePrecision-1) * 4);
	uint32_t index = 0;
	uint32_t indicesIndex = 0;
	uint32_t nextThetaIndex = 0;
	for (uint32_t i = 0; i < mLatitudePrecision - 1; i++)
	{
		for (uint32_t j = 0; j < mLongitudePrecision; j++)
		{
			index = i * mLongitudePrecision + j;
			mVertexAttributes.positions[index].x = mRadius * cos(thetaArray[i])*cos(phiArray[j]) + mCentre.x;
			mVertexAttributes.positions[index].y = mRadius * cos(thetaArray[i])*sin(phiArray[j]) + mCentre.y;
			mVertexAttributes.positions[index].z = mRadius * sin(thetaArray[i]) + mCentre.z;
			mVertexAttributes.normals[index].x = cos(thetaArray[i])*cos(phiArray[j]);
			mVertexAttributes.normals[index].y = cos(thetaArray[i])*sin(phiArray[j]);
			mVertexAttributes.normals[index].z = sin(thetaArray[i]);

			mVertexAttributes.colors[index].r = (mVertexAttributes.normals[index].x + 1) / 2;
			mVertexAttributes.colors[index].g = (mVertexAttributes.normals[index].y + 1) / 2;
			mVertexAttributes.colors[index].b = (mVertexAttributes.normals[index].z + 1) / 2;
			mVertexAttributes.colors[index].a = 1.0;


			mVertexAttributes.uvs[index].x = (phiArray[j]) / (2 * Math::PI);
			mVertexAttributes.uvs[index].y = (thetaArray[i] + Math::PI / 2) / (Math::PI);

			if(j!= mLongitudePrecision-1)
			{
				indicesIndex = i * (mLongitudePrecision-1) * 4 + 4 * j;
				nextThetaIndex = (i + 1) * mLongitudePrecision + j;
				mVertexAttributes.indices[indicesIndex] = index;
				mVertexAttributes.indices[indicesIndex + 1] = index + 1;
				mVertexAttributes.indices[indicesIndex + 2] = nextThetaIndex + 1;
				mVertexAttributes.indices[indicesIndex + 3] = nextThetaIndex;
			}
		}
	}

	for (uint32_t j = 0; j < mLongitudePrecision; j++)
	{
		index = (mLatitudePrecision - 1) * mLongitudePrecision + j;
		mVertexAttributes.positions[index].x = mRadius * cos(thetaArray[mLatitudePrecision - 1])*cos(phiArray[j]) + mCentre.x;
		mVertexAttributes.positions[index].y = mRadius * cos(thetaArray[mLatitudePrecision - 1])*sin(phiArray[j]) + mCentre.y;
		mVertexAttributes.positions[index].z = mRadius * sin(thetaArray[mLatitudePrecision - 1]) + mCentre.z;
		mVertexAttributes.normals[index].x = cos(thetaArray[mLatitudePrecision - 1])*cos(phiArray[j]);
		mVertexAttributes.normals[index].y = cos(thetaArray[mLatitudePrecision - 1])*sin(phiArray[j]);
		mVertexAttributes.normals[index].z = sin(thetaArray[mLatitudePrecision - 1]);
		mVertexAttributes.colors[index].r = (mVertexAttributes.normals[index].x + 1) / 2;
		mVertexAttributes.colors[index].g = (mVertexAttributes.normals[index].y + 1) / 2;
		mVertexAttributes.colors[index].b = (mVertexAttributes.normals[index].z + 1) / 2;
		mVertexAttributes.colors[index].a = 1.0;

		mVertexAttributes.uvs[index].x = (phiArray[j]) / (2 * Math::PI);
		mVertexAttributes.uvs[index].y = 1.0; 

	}


}

SceneNode* Sphere::getASphereNode(const glm::dvec3 &centre, const double &radius, const glm::uint &longitudePrecision, const glm::uint &latitudePrecision)
{
	SceneNode *node=new SceneNode;
	Sphere *sphere=new Sphere(centre, radius, longitudePrecision, latitudePrecision);
	sphere->setup();
	node->appendChild(sphere);
	return node;
}
