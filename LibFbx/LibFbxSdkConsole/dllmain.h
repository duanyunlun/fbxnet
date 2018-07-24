#pragma once
#include"gameobject.h"
#include"data.h"

extern "C" _declspec(dllexport) void* LoadGameObject(char* pname);
extern "C" _declspec(dllexport) void* CreateGameObject();
extern "C" _declspec(dllexport) void SaveGameObejct(void* pgameobject, char* pname);

extern "C" _declspec(dllexport) const int GetGameObjectName(void* pgameobject, char* pname);
extern "C" _declspec(dllexport) void SetGameObjectName(void* pgameobject, char* pname);

extern "C" _declspec(dllexport) void SetChildrenCount(void* pgameobject, int count);
extern "C" _declspec(dllexport) int GetChildrenCount(void* pgameobject);

extern "C" _declspec(dllexport) void* GetChild(void* pgameobject, int childIndex);
extern "C" _declspec(dllexport) void SetChild(void* pgameobject, int childIndex, void* pchild);

extern "C" _declspec(dllexport) void GetGeometricTransform(void* pgameobject, TransformData& transform);
extern "C" _declspec(dllexport) void SetGeometricTransform(void* pgameobject, TransformData transform);

extern "C" _declspec(dllexport) void GetTransform(void* pgameobject, TransformData& transform);
extern "C" _declspec(dllexport) void SetTransform(void* pgameobject, TransformData transform);

extern "C" _declspec(dllexport) void* GetMesh(void* pgameobject);

extern "C" _declspec(dllexport) int GetPolygonCount(void* pmesh);
extern "C" _declspec(dllexport) void SetPolygonCount(void* pmesh, int polygoncount);

extern "C" _declspec(dllexport) int GetUVSetCount(void* pmesh);
extern "C" _declspec(dllexport) void SetUVSetCount(void* pmesh, int uvsetcount);

extern "C" _declspec(dllexport) void GetPolygon(void* pmesh, int polygonIndex, PolygonData& polygondata);
extern "C" _declspec(dllexport) void SetPolygon(void* pmesh, int polygonIndex, PolygonData polygondata);

extern "C" _declspec(dllexport) void* GetRender(void* pgameobject);

extern "C" _declspec(dllexport) int GetMaterialCount(void* prender);
extern "C" _declspec(dllexport) void SetMaterialCount(void* prender, int materialcount);

extern "C" _declspec(dllexport) void GetMaterial(void* prender, int mertialIndex, MaterialData& materiadata);
extern "C" _declspec(dllexport) void SetMaterial(void* prender, int mertialIndex, MaterialData materiadata);

extern "C" _declspec(dllexport) void GetTexture(void* ptexture, TextureData& texturedata);
extern "C" _declspec(dllexport) void SetTexture(void* ptexture, TextureData texturedata);
extern "C" _declspec(dllexport) void* CreateTexture();

extern "C" _declspec(dllexport) void Destroy(void* pgameobject);
