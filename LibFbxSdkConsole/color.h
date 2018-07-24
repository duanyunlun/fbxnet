#pragma once

#include<fbxsdk.h>
#include"data.h"

struct Color
{
public:
	float mRed;
	float mGreen;
	float mBlue;
	float mAlpha;

public:
	Color();
	~Color();

public:
	void CopyFromFbxColor(const FbxColor * const pcolor);
	void CopyToFbxColor(FbxColor * const pcolor);
	FbxColor GetFbxColor();

	void CopyFromFbxDouble3(const FbxDouble3 * const pvector2);	
	void CopyToFbxDouble3(FbxDouble3 * const pVector2);
	FbxDouble3 GetFbxDouble3();

	void CopyFromColorData(const ColorData * const pdata);
	void CopyToColorData(ColorData * const pdata);
	ColorData GetColorData();
	
};