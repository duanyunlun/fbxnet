#include"gameobject.h"
#include"common.h"

GameObject::GameObject()
{
	mChildrenCount = 0;
	pChildren = NULL;
}

GameObject::~GameObject()
{
	if (pChildren)
	{
		delete[] pChildren;
		pChildren = NULL;
	}
}

void GameObject::Load(std::string strPath)
{
	FbxString pFilename = StdStr2FbxStr(strPath);
	FbxManager* pManager = FbxManager::Create();
	FbxIOSettings* pIOS = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(pIOS);
	FbxScene* pScene = FbxScene::Create(pManager, "My Scene");
	FbxImporter* pImporter = FbxImporter::Create(pManager, "");
	if (!pImporter->Initialize(pFilename, -1, pManager->GetIOSettings()))
	{
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", pImporter->GetStatus().GetErrorString());	
		return;
	}

	pImporter->Import(pScene);
	pImporter->Destroy();

	Load(pScene->GetRootNode());
	FbxGlobalSettings& globalSetting = pScene->GetGlobalSettings();
	 globalSetting.GetOriginalUpAxis();


	pManager->Destroy();
}

void  GameObject::Load(FbxNode* const pNode)
{
	mName = FbxStr2StdStr(pNode->GetNameOnly());
	mGeometryTransform.CopyFromFbxTransform(pNode);
	mTransform.CopyFromFbxTransform(pNode);
	mMesh.CopyFromFbxMesh(pNode->GetMesh());
	mRender.CopyFromFbxRender(pNode);
	mChildrenCount = pNode->GetChildCount();
	if (mChildrenCount!=0)
	{
		pChildren = new GameObject[mChildrenCount];
		for (int i = 0; i < mChildrenCount; i++)
		{
			pChildren[i].Load(pNode->GetChild(i));
		}
	}
}

void GameObject::Save(std::string strPath)
{
	FbxString pFilename = StdStr2FbxStr(strPath);
	FbxManager* pManager = FbxManager::Create();
	FbxIOSettings* pIOS = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(pIOS);
	FbxScene* pScene = FbxScene::Create(pManager, "My Scene");

	pScene->GetGlobalSettings().SetOriginalUpAxis(FbxAxisSystem::eMayaYUp);

	FbxNode* lNode = Save(pScene);
	pScene->AddNode(lNode);

	FbxExporter* lExporter = FbxExporter::Create(pManager, "");
	int pFileFormat = -1;
	if (pFileFormat < 0 || pFileFormat >= pManager->GetIOPluginRegistry()->GetWriterFormatCount())
	{
		// Write in fall back format in less no ASCII format found
		pFileFormat = pManager->GetIOPluginRegistry()->GetNativeWriterFormat();
		//Try to export in ASCII if possible
		int lFormatIndex, lFormatCount = pManager->GetIOPluginRegistry()->GetWriterFormatCount();
		for (lFormatIndex = 0; lFormatIndex<lFormatCount; lFormatIndex++)
		{
			if (pManager->GetIOPluginRegistry()->WriterIsFBX(lFormatIndex))
			{
				FbxString lDesc = pManager->GetIOPluginRegistry()->GetWriterFormatDescription(lFormatIndex);
				const char *lASCII = "ascii";
				if (lDesc.Find(lASCII) >= 0)
				{
					pFileFormat = lFormatIndex;
					break;
				}
			}
		}
	}

	lExporter->Initialize(pFilename, pFileFormat, pManager->GetIOSettings());
	lExporter->Export(pScene);
	lExporter->Destroy();
	pManager->Destroy();
}

FbxNode * GameObject::Save(FbxScene* pscene)
{
	FbxNode* lNode = FbxNode::Create(pscene, StdStr2FbxStr(mName));
	mTransform.CopyToFbxTransform(lNode);
	if (mMesh.mPolygonCount > 0) 
	{
		FbxMesh* pmesh = mMesh.GetFbxMesh(pscene);
		lNode->SetNodeAttribute(pmesh);
		lNode->SetShadingMode(FbxNode::eTextureShading);
	}
	if (mRender.mMaterialCount > 0)
	{
		mRender.CopyToFbxRender(lNode);
	}
	
	for (int i = 0; i < mChildrenCount; i++)
	{
		FbxNode* childNode = pChildren[i].Save(pscene);
		lNode->AddChild(childNode);
	}

	return lNode;
}