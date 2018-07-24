#include "dllmain.h"


void* LoadGameObject(char* path)
{
	GameObject* gameobject = new GameObject();
	gameobject->Load(path);

	return gameobject;
}

void* CreateGameObject()
{
	GameObject* gameobject = new GameObject();
	return gameobject;
}

void SaveGameObejct(void* pgameobject, char* path)
{
	GameObject* gameobject = (GameObject*)pgameobject;
	gameobject->Save(path);
}

const int GetGameObjectName(void* pgameobject, char* pname)
{
	GameObject* gameobject = (GameObject*)pgameobject;
	strcpy(pname, gameobject->mName.c_str());
	return gameobject->mName.length();
}

void SetGameObjectName(void* pgameobject, char* path)
{
	GameObject* gameobject = (GameObject*)pgameobject;
	gameobject->mName = path;
}

int GetChildrenCount(void* pgameobject)
{
	GameObject* gameobject = (GameObject*)pgameobject;
	return gameobject->mChildrenCount;
}

void SetChildrenCount(void* pgameobject, int count)
{
	GameObject* gameobject = (GameObject*)pgameobject;
	gameobject->mChildrenCount = count;
	if (gameobject->pChildren != NULL)
	{
		delete[] gameobject->pChildren;
	}
	gameobject->pChildren = new GameObject[count];
}

void* GetChild(void* pgameobject, int childIndex)
{
	GameObject* gameobject = (GameObject*)pgameobject;

	if (childIndex >= 0 && childIndex < gameobject->mChildrenCount)
	{
		return &gameobject->pChildren[childIndex];
	}
	return NULL;
}

void SetChild(void* pgameobject, int childIndex, void* pchild)
{
	GameObject* gameobject = (GameObject*)pgameobject;
	GameObject* child = (GameObject*)pchild;

	if (childIndex >= 0 && childIndex < gameobject->mChildrenCount)
	{
		memcpy(&gameobject->pChildren[childIndex], child, sizeof(GameObject));
	}
}

void GetGeometricTransform(void* pgameobject, TransformData& transform)
{
	GameObject* gameobject = (GameObject*)pgameobject;

	gameobject->mGeometryTransform.CopyToTransformData(&transform);
}

void SetGeometricTransform(void* pgameobject, TransformData transform)
{
	GameObject* gameobject = (GameObject*)pgameobject;
	gameobject->mGeometryTransform.CopyFromTransformData(&transform);
}

void GetTransform(void* pgameobject, TransformData& transform)
{
	GameObject* gameobject = (GameObject*)pgameobject;

	gameobject->mTransform.CopyToTransformData(&transform);
}

void SetTransform(void* pgameobject, TransformData transform)
{
	GameObject* gameobject = (GameObject*)pgameobject;
	gameobject->mTransform.CopyFromTransformData(&transform);
}

void* GetMesh(void* pgameobject)
{
	GameObject* gameobject = (GameObject*)pgameobject;
	return &gameobject->mMesh;
}


int GetPolygonCount(void* pmesh)
{
	Mesh* mesh = (Mesh*)pmesh;
	return mesh->mPolygonCount;
}

void SetPolygonCount(void* pmesh, int polygoncount)
{
	Mesh* mesh = (Mesh*)pmesh;
	mesh->mPolygonCount = polygoncount;
}

int GetUVSetCount(void* pmesh)
{
	Mesh* mesh = (Mesh*)pmesh;
	return mesh->mUVSetCount;
}

void SetUVSetCount(void* pmesh, int uvsetcount)
{
	Mesh* mesh = (Mesh*)pmesh;
	mesh->mUVSetCount = uvsetcount;

}

void GetPolygon(void* pmesh, int polygonIndex, PolygonData& polygondata)
{
	Mesh* mesh = (Mesh*)pmesh;
	if (polygonIndex >= 0 && polygonIndex < mesh->mPolygonCount)
	{
		mesh->pPolygon[polygonIndex].CopyToPolygonData(&polygondata);
	}
}

extern "C" _declspec(dllexport) void SetPolygon(void* pmesh, int polygonIndex, PolygonData polygondata)
{
	Mesh* mesh = (Mesh*)pmesh;
	if (polygonIndex >= 0 && polygonIndex < mesh->mPolygonCount)
	{
		mesh->pPolygon[polygonIndex].CopyFromPolygonData(&polygondata);
	}
}

void* GetRender(void* pgameobject)
{
	GameObject* gameobject = (GameObject*)pgameobject;
	return &gameobject->mRender;
}

int GetMaterialCount(void* prender)
{
	Render* render = (Render*)prender;
	return render->mMaterialCount;
}

void SetMaterialCount(void* prender, int materialcount)
{
	Render* render = (Render*)prender;
	render->mMaterialCount = materialcount;
}

void GetMaterial(void* prender, int mertialIndex, MaterialData& materiadata)
{
	Render* render = (Render*)prender;
	if (mertialIndex >= 0 && mertialIndex < render->mMaterialCount)
	{
		render->pMaterial[mertialIndex].CopyToMaterialData(&materiadata);
	}
}

void SetMaterial(void* prender, int mertialIndex, MaterialData materiadata)
{
	Render* render = (Render*)prender;
	if (mertialIndex >= 0 && mertialIndex < render->mMaterialCount)
	{
		render->pMaterial[mertialIndex].CopyFromMaterialData(&materiadata);
	}
}

void GetTexture(void* ptexture, TextureData& texturedata)
{
	Texture* texture = (Texture*)ptexture;
	texture->CopyToTextureData(&texturedata);
}

void SetTexture(void* ptexture, TextureData texturedata)
{
	Texture* texture = (Texture*)ptexture;
	texture->CopyFromTextureData(&texturedata);
}

void* CreateTexture()
{
	Texture* texture = new Texture();
	return texture;
}

void Destroy(void* pgameobject)
{
	delete pgameobject;
}