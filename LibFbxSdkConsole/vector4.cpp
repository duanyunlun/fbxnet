#include"vector4.h"

Vector4::Vector4()
{
	mX = 0;
	mY = 0;
	mZ = 0;
	mW = 0;
}

Vector4::~Vector4()
{

}

void Vector4::CopyFromFbxVector4(const FbxVector4 * const pvector4)
{
	mX = (float)pvector4->mData[0];
	mY = (float)pvector4->mData[1];
	mZ = (float)pvector4->mData[2];
	mW = (float)pvector4->mData[3];
}

void Vector4::CopyToFbxVector4(FbxVector4* const pvector4)
{
	pvector4->mData[0] = mX;
	pvector4->mData[1] = mY;
	pvector4->mData[2] = mZ;
	pvector4->mData[3] = mW;
}

FbxVector4 Vector4::GetFbxVector4()
{
	FbxVector4 vector4;
	CopyToFbxVector4(&vector4);
	return vector4;
}

void Vector4::CopyFromVector4Data(const Vector4Data * const pdata)
{
	mX = pdata->mX;
	mY = pdata->mY;
	mZ = pdata->mZ;
	mW = pdata->mW;
}

void Vector4::CopyToVector4Data(Vector4Data * const pdata)
{
	pdata->mX = mX;
	pdata->mY = mY;
	pdata->mZ = mZ;
	pdata->mW = mW;
}

Vector4Data Vector4::GetVector4Data()
{
	Vector4Data data;
	CopyToVector4Data(&data);
	return data;
}