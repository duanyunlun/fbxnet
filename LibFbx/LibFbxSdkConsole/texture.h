#pragma once

#include <string>
#include<fbxsdk.h>
#include"color.h"
#include"vector2.h"
#include"vector3.h"
#include"vector4.h"

struct Texture
{
public:
	std::string mName;
	int mTextureType;
	bool mSwapUV;
	Vector2 mTranslation;
	Vector2 mScale;
	Vector3 mRotation;
	std::string mRelativePath;
public:
	Texture();
	~Texture();

public:
	void CopyFromFbxTexture(const FbxTexture * const ptexture);
	void CopyToFbxTexture(FbxTexture * const ptexture);
	FbxTexture* GetFbxTexture(FbxScene* const psecne);

	void CopyFromTextureData(const TextureData * const pdata);
	void CopyToTextureData(TextureData * const pdata);
	TextureData GetTextureData();

};
