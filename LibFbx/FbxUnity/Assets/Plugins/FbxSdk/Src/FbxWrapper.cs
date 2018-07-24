using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.GLEx;

namespace FbxNet
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct Vector2Data
    {
        public float mX;
        public float mY;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct Vector3Data
    {
        public float mX;
        public float mY;
        public float mZ;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct Vector4Data
    {
        public float mX;
        public float mY;
        public float mZ;
        public float mW;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct ColorData
    {
        public float mRed;
        public float mGreen;
        public float mBlue;
        public float mAlpha;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct TextureData
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 1024)]
        public string mName;
        public int mTextureType;
        public bool mSwapUV;
        public Vector2Data mTranslation;
        public Vector2Data mScale;
        public Vector3Data mRotation;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 1024)]
        public string mRelativePath;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct PolygonData
    {
        public int mMaterialID;
        public int mUVSetCount;
        public int mCount;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public ColorData[] pColors;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public Vector3Data[] pVertices;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public Vector3Data[] pNormals;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public Vector3Data[] pTangents;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public Vector2Data[] pUVS;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public Vector2Data[] pUVS2;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public Vector2Data[] pUVS3;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public Vector2Data[] pUVS4;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct TransformData
    {
        public Vector3Data mPosition;
        public Vector3Data mRotation;
        public Vector3Data mScale;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 4)]
    public struct MaterialData
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 1024)]
        public string mName;
        public int mShaderType;// 0 Phong， 1 Lambert
        public ColorData mAmbient;
        public float mAmbientFactor;
        public IntPtr pAmbientTexture;
        public ColorData mDiffuse;
        public float mDiffuseFactor;
        public IntPtr pDiffuseTexture;
        public ColorData mSpecular;
        public float mSpecularFactor;
        public IntPtr pSpecularTexture;
        public ColorData mEmissive;
        public IntPtr pEmissiveTexture;
        public float mEmissiveFactor;
        public ColorData mTransparentColor;
        public float mTransparencyFactor;
        public ColorData mReflection;
        public float mReflectionFactor;
        public IntPtr pReflectionTexture;
        public float mShininess;
        public ColorData mNormalMap;
        public IntPtr pNormalTexture;
        public ColorData mBump;
        public float mBumpFactor;
        public IntPtr pBumpTexture;
    };

    public static class FbxInterface
    {
        #region fbxsdkbridge.dll functions

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr LoadGameObject(string ptah);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SaveGameObejct(IntPtr pgameobject, string name);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CreateGameObject();

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetGameObjectName(IntPtr pgameobject, byte[] name);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetGameObjectName(IntPtr pgameobject, string name);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetChildrenCount(IntPtr pgameobject);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetChildrenCount(IntPtr pgameobject, int count);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetChild(IntPtr pgameobject, int childIndex);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetChild(IntPtr pgameobject, int childIndex, IntPtr child);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetTransform(IntPtr pgameobject, ref TransformData transformdata);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetTransform(IntPtr pgameobject, TransformData transformdata);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetGeometricTransform(IntPtr pgameobject, ref TransformData transformdata);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetGeometricTransform(IntPtr pgameobject, TransformData transformdata);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetMesh(IntPtr pgameobject);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetPolygonCount(IntPtr pmesh);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetPolygonCount(IntPtr pmesh, int count);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetUVSetCount(IntPtr pmesh);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetUVSetCount(IntPtr pmesh, int count);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetPolygon(IntPtr pmesh, int polygonIndex, ref PolygonData polygondata);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetPolygon(IntPtr pmesh, int polygonIndex, PolygonData polygondata);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetRender(IntPtr pgameobject);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetMaterialCount(IntPtr prender);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetMaterialCount(IntPtr prender, int materialcount);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetMaterial(IntPtr prender, int mertialIndex, ref MaterialData materialdata);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetMaterial(IntPtr prender, int mertialIndex, MaterialData materialdata);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetTexture(IntPtr ptexture, ref TextureData texturedata);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetTexture(IntPtr ptexture, TextureData texturedata);

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CreateTexture();

        [DllImport("fbxsdkbridge", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Destroy(IntPtr pgameobject);

        #endregion

        #region public functions

        public static string GetGameObjectName(IntPtr pgameobject)
        {
            byte[] data = new byte[2048];
            int count = FbxInterface.GetGameObjectName(pgameobject, data);
            string name = System.Text.Encoding.Default.GetString(data, 0, count);
            return name;
        }

        public static List<GameObject> Load(string p_path)
        {
            IntPtr pGameObject = LoadGameObject(p_path);
            System.IO.FileInfo fileInfo = new System.IO.FileInfo(p_path);
            string directory = fileInfo.Directory.ToString();
            //GameObject gameObject = Load(pGameObject, new System.IO.FileInfo(p_path).Directory.ToString());
            List<GameObject> gameObjects = new List<GameObject>();
            int mChildrenCount = FbxInterface.GetChildrenCount(pGameObject);
            for (int i = 0; i < mChildrenCount; i++)
            {
                IntPtr childGameObject = FbxInterface.GetChild(pGameObject, i);
                GameObject gameObject = Load(childGameObject, directory);
                gameObjects.Add(gameObject);
            }

            FbxInterface.Destroy(pGameObject);

            return gameObjects;
        }

        static GameObject Load(IntPtr pGameObject, string p_directory, GameObject p_root = null)
        {
            string name = FbxInterface.GetGameObjectName(pGameObject);
            GameObject gameObject = new GameObject(name);
            if (p_root != null)
            {
                gameObject.transform.SetParent(p_root.transform);
            }
            Matrix4x4 matrix4X4 = GetGeometryMatrix(pGameObject);
            AttatchTransform(pGameObject, gameObject);
            AttachMesh(pGameObject, gameObject, matrix4X4);
            AttachRender(pGameObject, gameObject, p_directory);

            int mChildrenCount = FbxInterface.GetChildrenCount(pGameObject);
            for (int i = 0; i < mChildrenCount; i++)
            {
                IntPtr childGameObject = FbxInterface.GetChild(pGameObject, i);
                Load(childGameObject, p_directory, gameObject);
            }

            return gameObject;
        }

        #endregion

        #region private static functions

        static Matrix4x4 GetGeometryMatrix(IntPtr pGameObject)
        {
            TransformData transform = new TransformData();
            GetGeometricTransform(pGameObject, ref transform);

            Matrix4x4 matrix4X4 = new Matrix4x4();
            matrix4X4.SetTRS(transform.mPosition.ToVector3() / 100, Quaternion.Euler(transform.mRotation.ToVector3()), transform.mScale.ToVector3());

            return matrix4X4;
        }

        static void AttatchTransform(IntPtr pGameObject, GameObject p_gameObject)
        {
            TransformData transform = new TransformData();
            GetTransform(pGameObject, ref transform);
            Vector3 postion = transform.mPosition.ToVector3() / 100;
            p_gameObject.transform.position = new Vector3(-postion.x, postion.y, postion.z);
            p_gameObject.transform.rotation = Quaternion.Euler(-90, 0, 0) * Quaternion.Euler(transform.mRotation.ToVector3());
            p_gameObject.transform.localScale = transform.mScale.ToVector3();
        }

        static void AttachMesh(IntPtr pGameObject, GameObject p_gameObject, Matrix4x4 p_matrix)
        {
            IntPtr pMesh = FbxInterface.GetMesh(pGameObject);
            int polygonCount = FbxInterface.GetPolygonCount(pMesh);
            if (polygonCount == 0)
            {
            }
            else
            {
                List<Polygon3> polygons = new List<Polygon3>();
                for (int i = 0; i < polygonCount; i++)
                {
                    PolygonData polygon = new PolygonData();
                    FbxInterface.GetPolygon(pMesh, i, ref polygon);
                    polygons.Add(polygon.ToPolygon(p_matrix));
                }
                Mesh mesh = Polygon3.GenerateMesh(polygons);
                mesh.RecalculateBounds();
                mesh.RecalculateNormals();
                mesh.RecalculateTangents();
                p_gameObject.AddComponent<MeshFilter>().mesh = mesh;
            }
        }

        static void AttachRender(IntPtr pGameObject, GameObject p_gameObjec, string p_directory)
        {
            IntPtr render = FbxInterface.GetRender(pGameObject);
            int materialCount = FbxInterface.GetMaterialCount(render);
            if (materialCount == 0)
            {
            }
            else
            {
                List<Material> materials = new List<Material>();
                for (int i = 0; i < materialCount; i++)
                {
                    MaterialData material = new MaterialData();
                    FbxInterface.GetMaterial(render, i, ref material);
                    materials.Add(material.ToMaterial(p_directory));
                }

                p_gameObjec.AddComponent<MeshRenderer>().materials = materials.ToArray();
            }
        }

        #endregion

    }

}

