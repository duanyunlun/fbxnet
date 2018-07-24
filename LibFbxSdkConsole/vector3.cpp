#include"vector3.h"

Vector3::Vector3()
{
	mX = 0;
	mY = 0;
	mZ = 0;
}

Vector3::~Vector3()
{

}

void Vector3::CopyFromFbxVector4(const FbxVector4 * const pvector4)
{
	mX = (float)pvector4->mData[0];
	mY = (float)pvector4->mData[1];
	mZ = (float)pvector4->mData[2];
}

void Vector3::CopyToFbxVector4(FbxVector4* const pvector4)
{
	pvector4->mData[0] = mX;
	pvector4->mData[1] = mY;
	pvector4->mData[2] = mZ;
	pvector4->mData[3] = 1;
}

FbxVector4 Vector3::GetFbxVector4()
{
	FbxVector4 vector4;
	CopyToFbxVector4(&vector4);
	return vector4;
}

void Vector3::CopyFromFbxDouble3(const FbxDouble3 * const pdouble3)
{
	mX = (float)pdouble3->mData[0];
	mY = (float)pdouble3->mData[1];
	mZ = (float)pdouble3->mData[2];
}

void Vector3::CopyToFbxDouble3(FbxDouble3* const pdouble3)
{
	pdouble3->mData[0] = mX;
	pdouble3->mData[1] = mY;
	pdouble3->mData[2] = mZ;
}

FbxDouble3 Vector3::GetFbxDouble3()
{
	FbxDouble3 double3;
	CopyToFbxDouble3(&double3);
	return double3;
}

void Vector3::CopyFromVector3Data(const Vector3Data * const pdata)
{
	mX = pdata->mX;
	mY = pdata->mY;
	mZ = pdata->mZ;
}

void Vector3::CopyToVector3Data(Vector3Data * const pdata)
{
	pdata->mX = mX;
	pdata->mY = mY;
	pdata->mZ = mZ;
}

Vector3Data Vector3::GetVector3Data()
{
	Vector3Data data;
	CopyToVector3Data(&data);
	return data;
}