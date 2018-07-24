#pragma once
#include<fbxsdk.h>
#include"data.h"

struct Vector4
{
public:
	float mX;
	float mY;
	float mZ;
	float mW;


public:
	Vector4();
	~Vector4();

public:
	void CopyFromFbxVector4(const FbxVector4 * const pvector2);
	void CopyToFbxVector4(FbxVector4 * const pVector2);
	FbxVector4 GetFbxVector4();

	void CopyFromVector4Data(const Vector4Data * const pdata);
	void CopyToVector4Data(Vector4Data * const pdata);
	Vector4Data GetVector4Data();
};