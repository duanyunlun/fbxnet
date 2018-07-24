#include "mesh.h"
#include "common.h"

void ReadUV(int iPolyIndex, int iVertIndex, const FbxMesh* const pmesh, Polygon* const ppolygon, int lVertexCounter, int uvSetCount, const FbxGeometryElementUV** lUVElement);
void ReadNormal(int iPolyIndex, int iVertIndex, const FbxMesh* const pMesh, Polygon* const ppolygon, int lVertexCounter, const FbxGeometryElementNormal* lNormalElement);
void ReadTangent(int iPolyIndex, int iVertIndex, const FbxMesh* const pmesh, Polygon* const ppolygon, int lVertexCounter, const FbxGeometryElementTangent* lTangentElement);
void ReadColor(int iPolyIndex, int iVertIndex, const FbxMesh* const pMesh, Polygon* const ppolygon, int lVertexCounter, const FbxGeometryElementVertexColor* lColorElement);
void ReadMaterialID(int iPolyIndex, Polygon* const ppolygon, const FbxGeometryElementMaterial* lMaterialElement);

void WriteUV(int iPolyIndex, int iVertIndex, FbxMesh* const pMesh, Polygon* const ppolygon, FbxGeometryElementUV** const lUVElement, int UVSetCount);
void WriteNormal(int iPolyIndex, int iVertIndex, FbxMesh* const pMesh, Polygon* const ppolygon, FbxLayerElementNormal* const lLayerElementNormal);
void WriteTangent(int iPolyIndex, int iVertIndex, FbxMesh* const pMesh, Polygon* const ppolygon, FbxGeometryElementTangent* const lLayerElementTangent);
void WriteColor(int iPolyIndex, int iVertIndex, FbxMesh* const pMesh, Polygon* const ppolygon, FbxGeometryElementVertexColor* const lLayerElementColor);
void WriteMaterID(Polygon* const ppolygon, FbxGeometryElementMaterial* const lMaterialElement);

Mesh::Mesh()
{
	mPolygonCount = 0;
	mUVSetCount = 0;
	pUVSetNames = NULL;
	pPolygon = NULL;
}

Mesh::~Mesh()
{
	if (pUVSetNames)
	{
		delete[] pUVSetNames;
		pUVSetNames = NULL;
	}
	if (pPolygon)
	{
		delete[] pPolygon;
		pPolygon = NULL;

	}
}

void Mesh::CopyFromFbxMesh(const FbxMesh * const pmesh)
{
	if (!pmesh)
	{
		return;
	}
	mName = FbxStr2StdStr(pmesh->GetNameOnly());
	// uv set count
	FbxStringList lUVSetNameList;
	pmesh->GetUVSetNames(lUVSetNameList);
	mUVSetCount = lUVSetNameList.GetCount();
	if (mUVSetCount != 0)
	{
		pUVSetNames = new std::string[mUVSetCount];
		for (int i = 0; i < mUVSetCount; i++)
		{
			pUVSetNames[i] = FbxStr2StdStr(lUVSetNameList[i]);
		}
	}
	
	int polygonCount = pmesh->GetPolygonCount();
	mPolygonCount = polygonCount;
	pPolygon = new Polygon[polygonCount];

	FbxVector4* pCtrlPoints = pmesh->GetControlPoints();
	const FbxGeometryElementUV* pElementUV[10];
	for (int i = 0; i < mUVSetCount; i++)
	{
		FbxString lUVSetName = lUVSetNameList.GetStringAt(i);
		pElementUV[i] = pmesh->GetElementUV(lUVSetName);
	}
	const FbxGeometryElementNormal* lNormalElement = pmesh->GetElementNormal();
	const FbxGeometryElementTangent* lTangentElement = pmesh->GetElementTangent();
	const FbxGeometryElementVertexColor* lColorElement = pmesh->GetElementVertexColor();
	const FbxGeometryElementMaterial* lMaterialElement = pmesh->GetElementMaterial();

	int lVertexCounter = 0;
	for (int iPolyIndex = 0; iPolyIndex < polygonCount; iPolyIndex++)
	{
		const int verticeCount = pmesh->GetPolygonSize(iPolyIndex);

		Polygon& polygon = pPolygon[iPolyIndex];
		// vertice count
		polygon.mCount = verticeCount;
		polygon.mUVSetCount = mUVSetCount;

		//polygon.pVertices=new Vector3[verticeCount];
		//polygon.pColors = new Color[verticeCount];
		//polygon.pNormals = new Vector3[verticeCount];
		//polygon.pTangents=new  Vector3[verticeCount];
		//polygon.pUVS = new Vector2*[mUVSetCount];
		//for (int i = 0; i < mUVSetCount; i++)
		//{
		//	polygon.pUVS[i] = new Vector2[verticeCount];
		//}

		//const bool lUseIndex = lUVElement->GetReferenceMode() != FbxGeometryElement::eDirect;
		for (int iVertIndex = 0; iVertIndex < verticeCount; iVertIndex++)
		{
			int lPolyVertIndex = pmesh->GetPolygonVertex(iPolyIndex, iVertIndex);

			// read control vertex
			FbxVector4 position = pCtrlPoints[lPolyVertIndex];
			polygon.pVertices[iVertIndex].CopyFromFbxVector4(&position);
			// read UV
			for (int i = 0; i < mUVSetCount; i++)
			{
				ReadUV(iPolyIndex, iVertIndex, pmesh, &polygon, lVertexCounter, mUVSetCount, pElementUV);
			}
			// read normal
			ReadNormal(iPolyIndex, iVertIndex, pmesh, &polygon, lVertexCounter, lNormalElement);
			// read tangent
			ReadTangent(iPolyIndex, iVertIndex, pmesh, &polygon, lVertexCounter, lTangentElement);
			// read color
			ReadColor(iPolyIndex, iVertIndex, pmesh, &polygon, lVertexCounter, lColorElement);

			lVertexCounter++;
		}
		ReadMaterialID(iPolyIndex, &polygon, lMaterialElement);
	}
}

void Mesh::CopyToFbxMesh(FbxMesh * const pmesh)
{	
	// total vertice count
	int verticesCount = 0;
	for (int iPolygonIndex = 0; iPolygonIndex < mPolygonCount; iPolygonIndex++)
	{
		verticesCount += pPolygon[iPolygonIndex].mCount;
	}
	pmesh->InitControlPoints(verticesCount);
	FbxLayerElementNormal* lLayerElementNormal = pmesh->CreateElementNormal();
	lLayerElementNormal->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
	lLayerElementNormal->SetReferenceMode(FbxGeometryElement::eDirect);
	
	FbxGeometryElementUV* lUVElement[10];
	for (int i = 0; i < mUVSetCount; i++)
	{
		lUVElement[i] = pmesh->CreateElementUV(StdStr2FbxStr(pUVSetNames[i]));
		lUVElement[i]->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
		lUVElement[i]->SetReferenceMode(FbxGeometryElement::eDirect);
	}
	
	FbxGeometryElementTangent* lTangentElement = pmesh->CreateElementTangent();
	lTangentElement->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
	lTangentElement->SetReferenceMode(FbxGeometryElement::eDirect);
	FbxGeometryElementVertexColor* lColorElement = pmesh->CreateElementVertexColor();
	lColorElement->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
	lColorElement->SetReferenceMode(FbxGeometryElement::eDirect);

	FbxGeometryElementMaterial* lMaterialElement = pmesh->CreateElementMaterial();
	lMaterialElement->SetMappingMode(FbxGeometryElement::eByPolygon);
	lMaterialElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);

	FbxVector4* lControlPoints = pmesh->GetControlPoints();
	int lVertexCounter = 0;
	for (int iPolyIndex = 0; iPolyIndex < mPolygonCount; iPolyIndex++)
	{
		WriteMaterID(&pPolygon[iPolyIndex], lMaterialElement);
		pmesh->BeginPolygon(pPolygon[iPolyIndex].mMaterialID, -1, false);

		for (int iVertIndex = 0; iVertIndex < pPolygon[iPolyIndex].mCount; iVertIndex++)
		{
			lControlPoints[lVertexCounter] = pPolygon[iPolyIndex].pVertices[iVertIndex].GetFbxVector4();

			pmesh->AddPolygon(lVertexCounter);

			WriteUV(iPolyIndex, iVertIndex, pmesh, &pPolygon[iPolyIndex], lUVElement, mUVSetCount);
			WriteNormal(iPolyIndex, iVertIndex, pmesh, &pPolygon[iPolyIndex], lLayerElementNormal);
			WriteTangent(iPolyIndex, iVertIndex, pmesh, &pPolygon[iPolyIndex], lTangentElement);
			WriteColor(iPolyIndex, iVertIndex, pmesh, &pPolygon[iPolyIndex], lColorElement);

			lVertexCounter++;
		}

		pmesh->EndPolygon();
	}
}


FbxMesh* Mesh::GetFbxMesh(FbxScene * pscene)
{
	FbxMesh* lMesh = FbxMesh::Create(pscene, StdStr2FbxStr(mName));
	CopyToFbxMesh(lMesh);

	return lMesh;
}

// read uv
void ReadUV(int iPolyIndex, int iVertIndex, const FbxMesh* const pmesh, Polygon* const ppolygon, int lVertexCounter, int uvSetCount, const FbxGeometryElementUV** lUVElement)
{
	if (!lUVElement)
	{
		return;
	}
	for (int lUVSetIndex = 0; lUVSetIndex < uvSetCount; lUVSetIndex++)
	{
		if (lUVElement[lUVSetIndex]->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			int lPolyVertIndex = pmesh->GetPolygonVertex(iPolyIndex, iVertIndex);
			int lUVIndex = lUVElement[lUVSetIndex]->GetReferenceMode() == FbxGeometryElement::eDirect ? lPolyVertIndex :
				lUVElement[lUVSetIndex]->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lUVElement[lUVSetIndex]->GetIndexArray().GetAt(lPolyVertIndex) : 0;

			FbxVector2 lUVValue = lUVElement[lUVSetIndex]->GetDirectArray().GetAt(lUVIndex);
			if (lUVSetIndex == 0)
			{
				ppolygon->pUVS[iVertIndex].CopyFromFbxVector2(&lUVValue);
			}
			else if (lUVSetIndex == 1)
			{
				ppolygon->pUVS2[iVertIndex].CopyFromFbxVector2(&lUVValue);
			}
			else if (lUVSetIndex == 2)
			{
				ppolygon->pUVS3[iVertIndex].CopyFromFbxVector2(&lUVValue);
			}
			else if (lUVSetIndex == 3)
			{
				ppolygon->pUVS4[iVertIndex].CopyFromFbxVector2(&lUVValue);
			}
		}
		else if (lUVElement[lUVSetIndex]->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			if (lVertexCounter < lUVElement[lUVSetIndex]->GetIndexArray().GetCount())
			{
				int lUVIndex = lUVElement[lUVSetIndex]->GetReferenceMode() == FbxGeometryElement::eDirect ? lVertexCounter :
					lUVElement[lUVSetIndex]->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lUVElement[lUVSetIndex]->GetIndexArray().GetAt(lVertexCounter) : 0;

				FbxVector2 lUVValue = lUVElement[lUVSetIndex]->GetDirectArray().GetAt(lUVIndex);
				if (lUVSetIndex == 0)
				{
					ppolygon->pUVS[iVertIndex].CopyFromFbxVector2(&lUVValue);
				}
				else if (lUVSetIndex == 1)
				{
					ppolygon->pUVS2[iVertIndex].CopyFromFbxVector2(&lUVValue);
				}
				else if (lUVSetIndex == 2)
				{
					ppolygon->pUVS3[iVertIndex].CopyFromFbxVector2(&lUVValue);
				}
				else if (lUVSetIndex == 3)
				{
					ppolygon->pUVS4[iVertIndex].CopyFromFbxVector2(&lUVValue);
				}
			}
		}
	}
}
// read normal
void ReadNormal(int iPolyIndex, int iVertIndex, const FbxMesh* const pMesh, Polygon* const ppolygon, int lVertexCounter, const FbxGeometryElementNormal* lNormalElement)
{
	if (!lNormalElement)
	{
		return;
	}
	if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		int lPolyVertIndex = pMesh->GetPolygonVertex(iPolyIndex, iVertIndex);
		int lNormalIndex = lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect ? lPolyVertIndex :
			lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lNormalElement->GetIndexArray().GetAt(lPolyVertIndex) : 0;
		FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
		ppolygon->pNormals[iVertIndex].CopyFromFbxVector4(&lNormal);
	}
	else if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		int lNormalIndex = lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect ? lVertexCounter :
			lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lNormalIndex = lNormalElement->GetIndexArray().GetAt(lVertexCounter) : 0;
		FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
		ppolygon->pNormals[iVertIndex].CopyFromFbxVector4(&lNormal);
		lVertexCounter++;
	}
}
// read tangent
void ReadTangent(int iPolyIndex, int iVertIndex, const FbxMesh* const pmesh, Polygon* const ppolygon, int lVertexCounter, const FbxGeometryElementTangent* lTangentElement)
{
	if (!lTangentElement)
	{
		return;
	}
	if (lTangentElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		int lPolyVertIndex = pmesh->GetPolygonVertex(iPolyIndex, iVertIndex);
		int lTangentIndex = lTangentElement->GetReferenceMode() == FbxGeometryElement::eDirect ? lPolyVertIndex :
			lTangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lTangentElement->GetIndexArray().GetAt(lPolyVertIndex) : 0;
		FbxVector4 lTangent = lTangentElement->GetDirectArray().GetAt(lTangentIndex);
		ppolygon->pTangents[iVertIndex].CopyFromFbxVector4(&lTangent);
	}
	else if (lTangentElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		int lTangentIndex = lTangentElement->GetReferenceMode() == FbxGeometryElement::eDirect? lVertexCounter
			: lTangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect? lTangentElement->GetIndexArray().GetAt(lVertexCounter):0;
		FbxVector4 lTangent = lTangentElement->GetDirectArray().GetAt(lTangentIndex);
		ppolygon->pTangents[iVertIndex].CopyFromFbxVector4(&lTangent);
	}
}
// read uv
void ReadColor(int iPolyIndex, int iVertIndex, const FbxMesh* const pMesh, Polygon* const ppolygon, int lVertexCounter, const FbxGeometryElementVertexColor* lColorElement)
{
	if (!lColorElement)
	{
		return;
	}
	if (lColorElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		int lPolyVertIndex = pMesh->GetPolygonVertex(iPolyIndex, iVertIndex);
		int lColorIndex = lColorElement->GetReferenceMode() == FbxGeometryElement::eDirect? lPolyVertIndex:
			lColorElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lColorElement->GetIndexArray().GetAt(lPolyVertIndex):0;

		FbxColor lColor = lColorElement->GetDirectArray().GetAt(lColorIndex);
		ppolygon->pColors[iVertIndex].CopyFromFbxColor(&lColor);
	}
	else if (lColorElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		int lColorIndex = lColorElement->GetReferenceMode() == FbxGeometryElement::eDirect ? lVertexCounter :
			lColorElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect ? lColorElement->GetIndexArray().GetAt(lVertexCounter) : 0;

		FbxColor lColor = lColorElement->GetDirectArray().GetAt(lColorIndex);
		ppolygon->pColors[iVertIndex].CopyFromFbxColor(&lColor);
	}
}
// read material index
void ReadMaterialID(int iPolyIndex, Polygon* const ppolygon, const FbxGeometryElementMaterial* lMaterialElement)
{
	if (lMaterialElement->GetMappingMode() == FbxGeometryElement::eByPolygon)
	{
		int materialId = lMaterialElement->GetIndexArray().GetAt(iPolyIndex);
		ppolygon->mMaterialID = materialId;
	}
	else if (lMaterialElement->GetMappingMode() == FbxGeometryElement::eAllSame)
	{
		int materialId = lMaterialElement->GetIndexArray().GetAt(iPolyIndex);
		ppolygon->mMaterialID = materialId;
	}
}

// write uv
void WriteUV(int iPolyIndex, int iVertIndex, FbxMesh* const pMesh, Polygon* const ppolygon, FbxGeometryElementUV** const lUVElement, int UVSetCount)
{
	for (int lUVSetIndex = 0; lUVSetIndex < UVSetCount; lUVSetIndex++)
	{
		if (lUVSetIndex == 0)
		{
			lUVElement[lUVSetIndex]->GetDirectArray().Add(ppolygon->pUVS[iVertIndex].GetFbxVector2());
		}
		else if (lUVSetIndex == 1)
		{
			lUVElement[lUVSetIndex]->GetDirectArray().Add(ppolygon->pUVS2[iVertIndex].GetFbxVector2());
		}
		else if (lUVSetIndex == 2)
		{
			lUVElement[lUVSetIndex]->GetDirectArray().Add(ppolygon->pUVS3[iVertIndex].GetFbxVector2());
		}
		else if (lUVSetIndex == 3)
		{
			lUVElement[lUVSetIndex]->GetDirectArray().Add(ppolygon->pUVS4[iVertIndex].GetFbxVector2());
		}
	}
}
// write normal
void WriteNormal(int iPolyIndex, int iVertIndex, FbxMesh* const pMesh, Polygon* const ppolygon, FbxLayerElementNormal* const lLayerElementNormal)
{
	lLayerElementNormal->GetDirectArray().Add(ppolygon->pNormals[iVertIndex].GetFbxVector4());
}
// write tangent
void WriteTangent(int iPolyIndex, int iVertIndex, FbxMesh* const pMesh, Polygon* const ppolygon, FbxGeometryElementTangent* const lLayerElementTangent)
{
	lLayerElementTangent->GetDirectArray().Add(ppolygon->pTangents[iVertIndex].GetFbxVector4());
}
// write color
void WriteColor(int iPolyIndex, int iVertIndex, FbxMesh* const pMesh, Polygon* const ppolygon, FbxGeometryElementVertexColor* const lLayerElementColor)
{
	lLayerElementColor->GetDirectArray().Add(ppolygon->pColors[iVertIndex].GetFbxColor());
}
// WriteMaterID
void WriteMaterID(Polygon* const ppolygon, FbxGeometryElementMaterial* const lMaterialElement)
{
	//lMaterialElement->GetIndexArray
	lMaterialElement->GetIndexArray().Add(ppolygon->mMaterialID);
}
