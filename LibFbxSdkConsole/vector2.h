#pragma once
#include<fbxsdk.h>
#include"data.h"

struct Vector2
{
public:
	float mX;
	float mY;

public:
	Vector2();
	~Vector2();

public:
	void CopyFromFbxVector2(const FbxVector2 * const pvector2);
	void CopyToFbxVector2(FbxVector2 * const pVector2);
	FbxVector2 GetFbxVector2();

	void CopyFromVector2Data(const Vector2Data * const pdata);
	void CopyToVector2Data(Vector2Data * const pdata);
	Vector2Data GetVector2Data();

};
