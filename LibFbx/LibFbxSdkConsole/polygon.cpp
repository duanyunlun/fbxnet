#include "polygon.h"

Polygon::Polygon()
{
	mMaterialID = -1;
	mUVSetCount = 0;
	mCount = 0;
}

Polygon::~Polygon()
{

}

void Polygon::CopyFromPolygonData(const PolygonData * const pdata)
{
	mMaterialID = pdata->mMaterialID;
	mUVSetCount = pdata->mUVSetCount;
	mCount = pdata->mCount;
	for (int i = 0; i < mCount; i++)
	{
		pColors[i].CopyFromColorData(&pdata->pColors[i]);
		pVertices[i].CopyFromVector3Data(&pdata->pVertices[i]);
		pNormals[i].CopyFromVector3Data(&pdata->pNormals[i]);
		pTangents[i].CopyFromVector3Data(&pdata->pTangents[i]);
		pUVS[i].CopyFromVector2Data(&pdata->pUVS[i]);
		pUVS2[i].CopyFromVector2Data(&pdata->pUVS2[i]);
		pUVS3[i].CopyFromVector2Data(&pdata->pUVS3[i]);
		pUVS4[i].CopyFromVector2Data(&pdata->pUVS4[i]);

	}
}

void Polygon::CopyToPolygonData(PolygonData * const pdata)
{
	pdata->mMaterialID = mMaterialID;
	pdata->mUVSetCount = mUVSetCount;
	pdata->mCount = mCount;
	for (int i = 0; i < mCount; i++)
	{
		pColors[i].CopyToColorData(&pdata->pColors[i]);
		pVertices[i].CopyToVector3Data(&pdata->pVertices[i]);
		pNormals[i].CopyToVector3Data(&pdata->pNormals[i]);
		pTangents[i].CopyToVector3Data(&pdata->pTangents[i]);
		pUVS[i].CopyToVector2Data(&pdata->pUVS[i]);
		pUVS2[i].CopyToVector2Data(&pdata->pUVS2[i]);
		pUVS3[i].CopyToVector2Data(&pdata->pUVS3[i]);
		pUVS4[i].CopyToVector2Data(&pdata->pUVS4[i]);

	}
}

PolygonData Polygon::GetPolygonData()
{
	PolygonData data;
	CopyToPolygonData(&data);
	return data;
}