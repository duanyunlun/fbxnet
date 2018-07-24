#pragma once

#include<fbxsdk.h>
#include"color.h"
#include"vector2.h"
#include"vector3.h"
#include"vector4.h"
#include"string.h"
#include<string>


struct Polygon
{
public:
	int mMaterialID;
	int mUVSetCount;
	int mCount;
	Color pColors[8];
	Vector3 pVertices[8];
	Vector3 pNormals[8];
	Vector3 pTangents[8];
	Vector2 pUVS[8];
	Vector2 pUVS2[8];
	Vector2 pUVS3[8];
	Vector2 pUVS4[8];

public:
	Polygon();
	~Polygon();

public:
	void CopyFromPolygonData(const PolygonData * const pdata);
	void CopyToPolygonData(PolygonData * const pdata);
	PolygonData GetPolygonData();
};