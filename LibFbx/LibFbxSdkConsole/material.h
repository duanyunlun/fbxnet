#pragma once

#include <string>
#include<fbxsdk.h>
#include"color.h"
#include"vector2.h"
#include"vector3.h"
#include"vector4.h"
#include"string.h"
#include"texture.h"
#include"data.h"

struct Material
{
public:
	std::string mName;
	int mShaderType;// 0 Phong£¬ 1 Lambert
	Color mAmbient;
	float mAmbientFactor;
	Texture* pAmbientTexture;
	Color mDiffuse;
	float mDiffuseFactor;
	Texture* pDiffuseTexture;
	Color mSpecular;
	float mSpecularFactor;
	Texture* pSpecularTexture;
	Color mEmissive;
	Texture* pEmissiveTexture;
	float mEmissiveFactor;
	Color mTransparentColor;
	float mTransparencyFactor;
	Color mReflection;
	float mReflectionFactor;
	Texture* pReflectionTexture;
	float mShininess;
	Color mNormalMap;
	Texture* pNormalTexture;
	Color mBump;
	float mBumpFactor;
	Texture* pBumpTexture;

public:
	Material();
	~Material();

public:
	void CopyFromFbxMatrial(const FbxSurfaceMaterial * const pmaterial);
	void CopyToFbxMaterial(FbxSurfaceMaterial * const pmaterial);
	FbxSurfaceMaterial* GeFbxMaterial(FbxScene* pScene);

	void CopyFromMaterialData(const MaterialData * const pdata);
	void CopyToMaterialData(MaterialData * const pdata);
	MaterialData GetMaterialData();
};
