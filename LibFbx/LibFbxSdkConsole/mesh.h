#pragma once

#include <fbxsdk.h>
#include "polygon.h"
#include <string>

struct Mesh
{
public:
	std::string mName;
	int mPolygonCount;
	int mUVSetCount;
	std::string* pUVSetNames;
	Polygon* pPolygon;

public:
	Mesh();
	~Mesh();

public:
	void CopyFromFbxMesh(const FbxMesh * const pmesh);
	void CopyToFbxMesh(FbxMesh * const pmesh);
	FbxMesh* GetFbxMesh(FbxScene * pscene);
};