#include"vector2.h"


Vector2::Vector2()
{
	mX = 0;
	mY = 0;
}

Vector2::~Vector2()
{

}

void Vector2::CopyFromFbxVector2(const FbxVector2 * const pvector2)
{
	mX = (float)pvector2->mData[0];
	mY = (float)pvector2->mData[1];
}

void Vector2::CopyToFbxVector2(FbxVector2* pvector2)
{
	pvector2->mData[0] = mX;
	pvector2->mData[1] = mY;
}

FbxVector2 Vector2::GetFbxVector2()
{
	FbxVector2 vector2;
	CopyToFbxVector2(&vector2);

	return vector2;
}

void Vector2::CopyFromVector2Data(const Vector2Data * const pdata)
{
	mX = pdata->mX;
	mY = pdata->mY;
}

void Vector2::CopyToVector2Data(Vector2Data * const pdata)
{
	pdata->mX = mX;
	pdata->mY = mY;
}

Vector2Data Vector2::GetVector2Data()
{
	Vector2Data data;
	CopyToVector2Data(&data);
	return data;
}
