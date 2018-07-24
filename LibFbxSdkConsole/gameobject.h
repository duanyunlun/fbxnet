#pragma once

#include <string>
#include<fbxsdk.h>

#include"string.h"
#include"transform.h"
#include"mesh.h"
#include"render.h"
#include"geometrytransform.h"

struct GameObject
{
public:
	std::string mName;
	Transform mTransform;
	GeometryTransform mGeometryTransform;
	Mesh mMesh;
	Render mRender;

	int mChildrenCount;
	GameObject* pChildren;

public:
	GameObject();
	~GameObject();

	void Load(std::string strPath);
	void Load(FbxNode* const pnode);

	void Save(std::string strPath);
	FbxNode *  Save(FbxScene* pscene);
};