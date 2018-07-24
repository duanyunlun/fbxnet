#include"render.h"

Render::Render()
{
	mMaterialCount = 0;
	pMaterial = NULL;
}

Render::~Render()
{
	if (pMaterial)
	{
		delete[] pMaterial;
		pMaterial = NULL;
	}
}

void Render::CopyFromFbxRender(const FbxNode * const pnode)
{
	mMaterialCount = pnode->GetMaterialCount();
	if (mMaterialCount)
	{
		pMaterial = new Material[mMaterialCount];
		for (int iMaterialIndex = 0; iMaterialIndex < mMaterialCount; iMaterialIndex++)
		{
			pMaterial[iMaterialIndex].CopyFromFbxMatrial(pnode->GetMaterial(iMaterialIndex));
		}
	}
}

void Render::CopyToFbxRender(FbxNode * const pnode)
{
	for (int iMaterialIndex = 0; iMaterialIndex < mMaterialCount; iMaterialIndex++)
	{
		FbxSurfaceMaterial* pmaterial = pMaterial[iMaterialIndex].GeFbxMaterial(pnode->GetScene());
		if (pmaterial)
		{
			pnode->AddMaterial(pmaterial);
		}
	}
}
