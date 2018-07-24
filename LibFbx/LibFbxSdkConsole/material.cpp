#include"material.h"
#include"common.h"

Material::Material()
{
	mShaderType = 0;
	mAmbient.mRed = 1;
	mAmbient.mGreen = 1;
	mAmbient.mBlue = 1;
	mAmbient.mAlpha = 1;
	mAmbientFactor = 1;
	pAmbientTexture = NULL;

	mDiffuse.mRed = 1;
	mDiffuse.mGreen = 1;
	mDiffuse.mBlue = 1;
	mDiffuse.mAlpha = 1;
	mDiffuseFactor = 1;
	pDiffuseTexture = NULL;

	mSpecular.mRed = 0;
	mSpecular.mGreen = 0;
	mSpecular.mBlue = 0;
	mSpecular.mAlpha = 0;
	mSpecularFactor = .3f;
	pSpecularTexture = NULL;

	mEmissive.mRed = 0;
	mEmissive.mGreen = 0;
	mEmissive.mBlue = 0;
	mEmissive.mAlpha = 0;
	mEmissiveFactor = 0;
	pEmissiveTexture = NULL;

	mTransparentColor.mRed = 0;
	mTransparentColor.mGreen = 0;
	mTransparentColor.mBlue = 0;
	mTransparentColor.mAlpha = 0;
	mTransparencyFactor = 0;

	mReflection.mRed = 1;
	mReflection.mGreen = 1;
	mReflection.mBlue = 1;
	mReflection.mAlpha = 1;
	mReflectionFactor = 0;
	pReflectionTexture = NULL;

	mShininess = 1;

	mNormalMap.mRed = 1;
	mNormalMap.mGreen = 1;
	mNormalMap.mBlue = 1;
	mNormalMap.mAlpha = 1;
	pNormalTexture = NULL;

	mBump.mRed = 0;
	mBump.mGreen = 0;
	mBump.mBlue = 0;
	mBump.mAlpha = 0;
	mBumpFactor = 0;
	pBumpTexture = NULL;

}

Material::~Material()
{
	if (pAmbientTexture)
	{
		delete pAmbientTexture;
	}
	if (pDiffuseTexture)
	{
		delete pDiffuseTexture;
	}
	if (pSpecularTexture)
	{
		delete pSpecularTexture;
	}
	if (pEmissiveTexture)
	{
		delete pEmissiveTexture;
	}
	if (pReflectionTexture)
	{
		delete pReflectionTexture;
	}
	if (pNormalTexture)
	{
		delete pNormalTexture;
	}
	if (pBumpTexture)
	{
		delete pBumpTexture;
	}
}

void Material::CopyFromFbxMatrial(const FbxSurfaceMaterial * const pmaterial)
{

	if (pmaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
	{
		mName = FbxStr2StdStr(pmaterial->GetNameOnly());
		mShaderType = 0;
		FbxSurfacePhong* phong = (FbxSurfacePhong*)pmaterial;
		mName = FbxStr2StdStr(phong->GetNameOnly());
		mAmbient.CopyToFbxDouble3(&phong->Ambient.Get());
		mAmbientFactor = (float)phong->AmbientFactor.Get();
		mDiffuse.CopyFromFbxDouble3(&phong->Diffuse.Get());
		mDiffuseFactor = (float)phong->DiffuseFactor.Get();
		mSpecular.CopyFromFbxDouble3(&phong->Specular.Get());
		mSpecularFactor = (float)phong->SpecularFactor.Get();
		mEmissive.CopyFromFbxDouble3(&phong->Emissive.Get());
		mEmissiveFactor = (float)phong->EmissiveFactor.Get();
		mTransparentColor.CopyFromFbxDouble3(&phong->TransparentColor.Get());
		mTransparencyFactor = (float)phong->TransparencyFactor.Get();
		mReflection.CopyFromFbxDouble3(&phong->Reflection.Get());
		mReflectionFactor = (float)phong->ReflectionFactor.Get();
		mBump.CopyFromFbxDouble3(&phong->Bump.Get());
		mBumpFactor = (float)phong->BumpFactor.Get();
		mNormalMap.CopyFromFbxDouble3(&phong->NormalMap.Get());

		mShininess = (float)phong->Shininess.Get();

		FbxTexture* pTexture = phong->Diffuse.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pDiffuseTexture = new Texture();
			pDiffuseTexture->CopyFromFbxTexture(pTexture);
		}
		pTexture = phong->Emissive.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pEmissiveTexture = new Texture();
			pEmissiveTexture->CopyFromFbxTexture(pTexture);
		}
		pTexture = phong->Ambient.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pAmbientTexture = new Texture();
			pAmbientTexture->CopyFromFbxTexture(pTexture);
		}
		pTexture = phong->Specular.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pSpecularTexture = new Texture();
			pSpecularTexture->CopyFromFbxTexture(pTexture);
		}
		pTexture = phong->Reflection.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pReflectionTexture = new Texture();
			pReflectionTexture->CopyFromFbxTexture(pTexture);
		}
		pTexture = phong->Bump.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pBumpTexture = new Texture();
			pBumpTexture->CopyFromFbxTexture(pTexture);
		}
		pTexture = phong->NormalMap.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pNormalTexture = new Texture();
			pNormalTexture->CopyFromFbxTexture(pTexture);
		}
	}
	else if (pmaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
	{
		mName = FbxStr2StdStr(pmaterial->GetNameOnly());
		mShaderType = 1;
		FbxSurfaceLambert* lambert = (FbxSurfaceLambert*)pmaterial;
		mName = FbxStr2StdStr(lambert->GetNameOnly());
		mAmbient.CopyToFbxDouble3(&lambert->Ambient.Get());
		mAmbientFactor = (float)lambert->AmbientFactor.Get();
		mDiffuse.CopyFromFbxDouble3(&lambert->Diffuse.Get());
		mDiffuseFactor = (float)lambert->DiffuseFactor.Get();
		mEmissive.CopyFromFbxDouble3(&lambert->Emissive.Get());
		mEmissiveFactor = (float)lambert->EmissiveFactor.Get();
		mTransparentColor.CopyFromFbxDouble3(&lambert->TransparentColor.Get());
		mTransparencyFactor = (float)lambert->TransparencyFactor.Get();
		mBump.CopyFromFbxDouble3(&lambert->Bump.Get());
		mBumpFactor = (float)lambert->BumpFactor.Get();
		mNormalMap.CopyFromFbxDouble3(&lambert->NormalMap.Get());

		FbxTexture* pTexture = lambert->Diffuse.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pDiffuseTexture = new Texture();
			pDiffuseTexture->CopyFromFbxTexture(pTexture);
		}
		pTexture = lambert->Emissive.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pEmissiveTexture = new Texture();
			pEmissiveTexture->CopyFromFbxTexture(pTexture);
		}
		pTexture = lambert->Ambient.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pAmbientTexture = new Texture();
			pAmbientTexture->CopyFromFbxTexture(pTexture);
		}
		pTexture = lambert->Bump.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pBumpTexture = new Texture();
			pBumpTexture->CopyFromFbxTexture(pTexture);
		}
		pTexture = lambert->NormalMap.GetSrcObject<FbxTexture>();
		if (pTexture)
		{
			pNormalTexture = new Texture();
			pNormalTexture->CopyFromFbxTexture(pTexture);
		}
	}
}

void Material::CopyToFbxMaterial(FbxSurfaceMaterial * const pmaterial)
{
	if (pmaterial->GetClassId().Is(FbxSurfacePhong::ClassId) && mShaderType==0)
	{
		FbxSurfacePhong* phong = (FbxSurfacePhong*)pmaterial;
		phong->Ambient.Set(FbxDouble3(mAmbient.mRed,mAmbient.mGreen,mAmbient.mBlue));
		phong->AmbientFactor.Set(mAmbientFactor);
		phong->Diffuse.Set(FbxDouble3(mDiffuse.mRed, mDiffuse.mGreen, mDiffuse.mBlue));
		phong->DiffuseFactor.Set(mDiffuseFactor);
		phong->Specular.Set(FbxDouble3(mSpecular.mRed, mSpecular.mGreen, mSpecular.mBlue));
		phong->SpecularFactor.Set(mSpecularFactor);
		phong->Emissive.Set(FbxDouble3(mEmissive.mRed, mEmissive.mGreen, mEmissive.mBlue));
		phong->EmissiveFactor.Set(mEmissiveFactor);
		phong->TransparentColor.Set(FbxDouble3(mTransparentColor.mRed, mTransparentColor.mGreen, mTransparentColor.mBlue));
		phong->TransparencyFactor.Set(mTransparencyFactor);
		phong->Reflection.Set(FbxDouble3(mReflection.mRed, mReflection.mGreen, mReflection.mBlue));
		phong->ReflectionFactor.Set(mReflectionFactor);
		phong->Bump.Set(FbxDouble3(mBump.mRed, mBump.mGreen, mBump.mBlue));
		phong->BumpFactor.Set(mBumpFactor);

		phong->NormalMap.Set(FbxDouble3(mNormalMap.mRed, mNormalMap.mGreen, mNormalMap.mBlue));

		phong->Shininess.Set(mShininess);
		phong->ShadingModel.Set("Phong");

		if (pDiffuseTexture)
		{
			FbxTexture* pTexture = pDiffuseTexture->GetFbxTexture(pmaterial->GetScene());
			phong->Diffuse.ConnectSrcObject(pTexture);
		}
		if (pEmissiveTexture)
		{
			FbxTexture* pTexture = pEmissiveTexture->GetFbxTexture(pmaterial->GetScene());
			phong->Emissive.ConnectSrcObject(pTexture);
		}
		if (pAmbientTexture)
		{
			FbxTexture* pTexture = pAmbientTexture->GetFbxTexture(pmaterial->GetScene());
			phong->Ambient.ConnectSrcObject(pTexture);
		}
		if (pSpecularTexture)
		{
			FbxTexture* pTexture = pSpecularTexture->GetFbxTexture(pmaterial->GetScene());
			phong->Specular.ConnectSrcObject(pTexture);
		}
		if (pReflectionTexture)
		{
			FbxTexture* pTexture = pReflectionTexture->GetFbxTexture(pmaterial->GetScene());
			phong->Reflection.ConnectSrcObject(pTexture);
		}
		if (pBumpTexture)
		{
			FbxTexture* pTexture = pBumpTexture->GetFbxTexture(pmaterial->GetScene());
			phong->Bump.ConnectSrcObject(pTexture);
		}
		if (pNormalTexture)
		{
			FbxTexture* pTexture = pNormalTexture->GetFbxTexture(pmaterial->GetScene());
			phong->NormalMap.ConnectSrcObject(pTexture);
		}
	}
	else if (pmaterial->GetClassId().Is(FbxSurfaceLambert::ClassId) && mShaderType == 1)
	{
		FbxSurfaceLambert* lambert = (FbxSurfaceLambert*)pmaterial;
		lambert->Ambient.Set(FbxDouble3(mAmbient.mRed, mAmbient.mGreen, mAmbient.mBlue));
		lambert->AmbientFactor.Set(mAmbientFactor);
		lambert->Diffuse.Set(FbxDouble3(mDiffuse.mRed, mDiffuse.mGreen, mDiffuse.mBlue));
		lambert->DiffuseFactor.Set(mDiffuseFactor);
		lambert->Emissive.Set(FbxDouble3(mEmissive.mRed, mEmissive.mGreen, mEmissive.mBlue));
		lambert->EmissiveFactor.Set(mEmissiveFactor);
		lambert->TransparentColor.Set(FbxDouble3(mTransparentColor.mRed, mTransparentColor.mGreen, mTransparentColor.mBlue));
		lambert->TransparencyFactor.Set(mTransparencyFactor);
		lambert->Bump.Set(FbxDouble3(mBump.mRed, mBump.mGreen, mBump.mBlue));
		lambert->BumpFactor.Set(mBumpFactor);

		lambert->NormalMap.Set(FbxDouble3(mNormalMap.mRed, mNormalMap.mGreen, mNormalMap.mBlue));
		lambert->ShadingModel.Set("Lambert");

		if (pDiffuseTexture)
		{
			FbxTexture* pTexture = pDiffuseTexture->GetFbxTexture(pmaterial->GetScene());
			lambert->Diffuse.ConnectSrcObject(pTexture);
		}
		if (pEmissiveTexture)
		{
			FbxTexture* pTexture = pEmissiveTexture->GetFbxTexture(pmaterial->GetScene());
			lambert->Emissive.ConnectSrcObject(pTexture);
		}
		if (pAmbientTexture)
		{
			FbxTexture* pTexture = pAmbientTexture->GetFbxTexture(pmaterial->GetScene());
			lambert->Ambient.ConnectSrcObject(pTexture);
		}
		if (pBumpTexture)
		{
			FbxTexture* pTexture = pBumpTexture->GetFbxTexture(pmaterial->GetScene());
			lambert->Bump.ConnectSrcObject(pTexture);
		}
		if (pNormalTexture)
		{
			FbxTexture* pTexture = pNormalTexture->GetFbxTexture(pmaterial->GetScene());
			lambert->NormalMap.ConnectSrcObject(pTexture);
		}
	}
}

FbxSurfaceMaterial* Material::GeFbxMaterial(FbxScene* pScene)
{
	if (mShaderType == 0)
	{
		FbxSurfacePhong *lMaterial = FbxSurfacePhong::Create(pScene, StdStr2FbxStr(mName));
		CopyToFbxMaterial(lMaterial);

		return lMaterial;
	}
	else if (mShaderType == 1)
	{
		FbxSurfaceLambert* lMaterial = FbxSurfaceLambert::Create(pScene, StdStr2FbxStr(mName));
		CopyToFbxMaterial(lMaterial);

		return lMaterial;
	}
	else
	{
		return NULL;
	}
}

void Material::CopyFromMaterialData(const MaterialData * const pdata)
{
	char buffer[1024];
	//memset(buffer, 0, 1024);
	//memcpy(buffer, pdata->mName, pdata->mNameLength);
	//mName = buffer;
	strcpy(buffer, pdata->mName);
	mName = buffer;
	mShaderType = pdata->mShaderType;
	mAmbient.CopyFromColorData(&pdata->mAmbient);
	mAmbientFactor = pdata->mAmbientFactor;
	pAmbientTexture = (Texture*)pdata->pAmbientTexture;
	mDiffuse.CopyFromColorData(&pdata->mDiffuse);
	mDiffuseFactor = pdata->mDiffuseFactor;
	pDiffuseTexture = (Texture*)pdata->pDiffuseTexture;
	mSpecular.CopyFromColorData(&pdata->mSpecular);
	mSpecularFactor = pdata->mSpecularFactor;
	pSpecularTexture = (Texture*)pdata->pSpecularTexture;
	mEmissive.CopyFromColorData(&pdata->mEmissive);
	mEmissiveFactor = pdata->mEmissiveFactor;
	pEmissiveTexture = (Texture*)pdata->pEmissiveTexture;
	mTransparentColor.CopyFromColorData(&pdata->mTransparentColor);
	mTransparencyFactor = pdata->mTransparencyFactor;
	mReflection.CopyFromColorData(&pdata->mReflection);
	mReflectionFactor = pdata->mReflectionFactor;
	pReflectionTexture = (Texture*)pdata->pReflectionTexture;
	mShininess = pdata->mShininess;
	mNormalMap.CopyFromColorData(&pdata->mNormalMap);
	pNormalTexture = (Texture*)pdata->pNormalTexture;
	mBump.CopyFromColorData(&pdata->mBump);
	mBumpFactor = pdata->mBumpFactor;
	pBumpTexture = (Texture*)pdata->pBumpTexture;
}

void Material::CopyToMaterialData(MaterialData * const pdata)
{
	//pdata->mNameLength = mName.length();
	//memset(pdata->mName, 0, sizeof(pdata->mName));
	//memcpy(pdata->mName, mName.c_str(), mName.length());
	strcpy(pdata->mName, mName.c_str());
	pdata->mShaderType = mShaderType;
	mAmbient.CopyToColorData(&pdata->mAmbient);
	pdata->mAmbientFactor = mAmbientFactor;
	pdata->pAmbientTexture = pAmbientTexture;
	mDiffuse.CopyToColorData(&pdata->mDiffuse);
	pdata->mDiffuseFactor = mDiffuseFactor;
	pdata->pDiffuseTexture = pDiffuseTexture;
	mSpecular.CopyToColorData(&pdata->mSpecular);
	pdata->mSpecularFactor = mSpecularFactor;
	pdata->pSpecularTexture = pSpecularTexture;
	mEmissive.CopyToColorData(&pdata->mEmissive);
	pdata->mEmissiveFactor = mEmissiveFactor;
	pdata->pEmissiveTexture = pEmissiveTexture;
	mTransparentColor.CopyToColorData(&pdata->mTransparentColor);
	pdata->mTransparencyFactor = mTransparencyFactor;
	mReflection.CopyToColorData(&pdata->mReflection);
	pdata->mReflectionFactor = mReflectionFactor;
	pdata->pReflectionTexture = pReflectionTexture;
	pdata->mShininess = mShininess;
	mNormalMap.CopyToColorData(&pdata->mNormalMap);
	pdata->pNormalTexture = pNormalTexture;
	mBump.CopyToColorData(&pdata->mBump);
	pdata->mBumpFactor = mBumpFactor;
	pdata->pBumpTexture = pBumpTexture;
}

MaterialData Material::GetMaterialData()
{
	MaterialData data;
	CopyToMaterialData(&data);
	return data;
}
