#include"color.h"

Color::Color()
{
	mRed = 1;
	mGreen = 1;
	mBlue = 1;
	mAlpha = 1;
}

Color::~Color()
{}

void Color::CopyFromFbxColor(const FbxColor  *  const pcolor)
{
	mRed = (float)pcolor->mRed;
	mGreen = (float)pcolor->mGreen;
	mBlue = (float)pcolor->mBlue;
	mAlpha = (float)pcolor->mAlpha;
}

void Color::CopyToFbxColor(FbxColor  * const pcolor)
{
	pcolor->mAlpha = mAlpha;
	pcolor->mRed = mRed;
	pcolor->mBlue = mBlue;
	pcolor->mGreen = mGreen;
}

FbxColor Color::GetFbxColor()
{
	FbxColor color;
	CopyToFbxColor(&color);
	return color;
}

void Color::CopyFromFbxDouble3(const FbxDouble3  *  const pdouble3)
{
	mRed = (float)pdouble3->mData[0];
	mGreen = (float)pdouble3->mData[1];
	mBlue = (float)pdouble3->mData[2];
	mAlpha = 1;
}

void Color::CopyToFbxDouble3(FbxDouble3  * const pdouble3)
{
	pdouble3->mData[0] = mRed;
	pdouble3->mData[1] = mGreen;
	pdouble3->mData[2] = mBlue;
	pdouble3->mData[3] = 1;
}

FbxDouble3 Color::GetFbxDouble3()
{
	FbxDouble3 double3;
	CopyToFbxDouble3(&double3);
	return double3;
}

void Color::CopyFromColorData(const ColorData * const pdata)
{
	mRed = pdata->mRed;
	mBlue = pdata->mBlue;
	mGreen = pdata->mGreen;
	mAlpha = pdata->mAlpha;
}

void Color::CopyToColorData(ColorData * const pdata)
{
	pdata->mRed = mRed;
	pdata->mBlue = mBlue;
	pdata->mGreen = mGreen;
	pdata->mAlpha = mAlpha;
}

ColorData Color::GetColorData()
{
	ColorData data;
	CopyToColorData(&data);
	return data;
}