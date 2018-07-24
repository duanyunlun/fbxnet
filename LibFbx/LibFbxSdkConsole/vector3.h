#pragma once

#include<fbxsdk.h>
#include"data.h"

struct Vector3
{
public:
	float mX;
	float mY;
	float mZ;

public:
	Vector3();
	~Vector3();

public:
	void CopyFromFbxVector4(const FbxVector4 * const pvector2);
	void CopyToFbxVector4(FbxVector4 * const pVector2);
	FbxVector4 GetFbxVector4();

	void CopyFromFbxDouble3(const FbxDouble3 * const pvector2);
	void CopyToFbxDouble3(FbxDouble3 * const pVector2);
	FbxDouble3 GetFbxDouble3();

	void CopyFromVector3Data(const Vector3Data * const pdata);
	void CopyToVector3Data(Vector3Data * const pdata);
	Vector3Data GetVector3Data();
};