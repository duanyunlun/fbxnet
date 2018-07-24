#pragma once

//struct StringData
//{
//public:
//	int Size;
//	unsigned char Data[1024];
//};

struct Vector2Data
{
public:
	float mX;
	float mY;
};

struct Vector3Data
{
public:
	float mX;
	float mY;
	float mZ;
};

struct Vector4Data
{
public:
	float mX;
	float mY;
	float mZ;
	float mW;
};

struct ColorData
{
public:
	float mRed;
	float mGreen;
	float mBlue;
	float mAlpha;
};

struct TextureData
{
	//int mNameLength;
	//char mName[1024];
	char mName[1024];
	int mTextureType;
	bool mSwapUV;
	Vector2Data mTranslation;
	Vector2Data mScale;
	Vector3Data mRotation;
	//int mRelativePathLength;
	//char mRelativePath[1024];
	char mRelativePath[1024];
};

struct PolygonData
{
public:
	int mMaterialID;
	int mUVSetCount;
	int mCount;
	ColorData pColors[100];
	Vector3Data pVertices[100];
	Vector3Data pNormals[100];
	Vector3Data pTangents[100];
	Vector2Data pUVS[100];
	Vector2Data pUVS2[100];
	Vector2Data pUVS3[100];
	Vector2Data pUVS4[100];
};

struct TransformData
{
public:
	Vector3Data mPosition;
	Vector3Data mRotation;
	Vector3Data mScale;
};

struct MaterialData
{
public:
	char mName[1024];
	int mShaderType;// 0 Phong£¬ 1 Lambert
	ColorData mAmbient;
	float mAmbientFactor;
	void* pAmbientTexture;
	ColorData mDiffuse;
	float mDiffuseFactor;
	void* pDiffuseTexture;
	ColorData mSpecular;
	float mSpecularFactor;
	void* pSpecularTexture;
	ColorData mEmissive;
	void* pEmissiveTexture;
	float mEmissiveFactor;
	ColorData mTransparentColor;
	float mTransparencyFactor;
	ColorData mReflection;
	float mReflectionFactor;
	void* pReflectionTexture;
	float mShininess;
	ColorData mNormalMap;
	void* pNormalTexture;
	ColorData mBump;
	float mBumpFactor;
	void* pBumpTexture;
};
