#pragma once
#include<fbxsdk.h>
#include"material.h"
struct Render
{
public:
	int mMaterialCount;
	Material* pMaterial;

public:
	Render();
	~Render();

public:
	void CopyFromFbxRender(const FbxNode * const pnode);
	void CopyToFbxRender(FbxNode * const pmaterial);
};