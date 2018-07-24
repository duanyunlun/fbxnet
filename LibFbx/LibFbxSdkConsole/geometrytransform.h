#pragma once
#include <string>
#include<fbxsdk.h>
#include"color.h"
#include"vector2.h"
#include"vector3.h"
#include"vector4.h"
#include"string.h"

struct GeometryTransform
{
public:
	Vector3 mPosition;
	Vector3 mRotation;
	Vector3 mScale;

public:
	void CopyFromFbxTransform(const FbxNode * const ptransform);
	void CopyToFbxTransform(FbxNode * const ptransform);

	void CopyFromTransformData(const TransformData * const pdata);
	void CopyToTransformData(TransformData * const pdata);
	TransformData GetTransformData();

};