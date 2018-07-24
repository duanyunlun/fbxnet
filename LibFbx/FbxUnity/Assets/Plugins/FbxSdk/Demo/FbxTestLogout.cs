using FbxNet;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FbxTestLogout : MonoBehaviour {

	// Use this for initialization
	void Start ()
    {
        IntPtr pGameObject = FbxInterface.LoadGameObject("C:\\Users\\pengu\\Desktop\\aaa.FBX");
        PrintGameObject(pGameObject);
        FbxInterface.Destroy(pGameObject);
    }

    static void PrintGameObject(IntPtr pGameObject)
    {
        PrintTransform(pGameObject);
        PrintMesh(pGameObject);
        PrintRender(pGameObject);
        int mChildrenCount = FbxInterface.GetChildrenCount(pGameObject);
        Debug.LogFormat("mChildrenCount：{0}", 0);
        for (int i = 0; i < mChildrenCount; i++)
        {
            IntPtr childGameObject = FbxInterface.GetChild(pGameObject, i);
            PrintGameObject(childGameObject);
        }
    }

    static void PrintTransform(IntPtr pGameObject)
    {
        TransformData transform = new TransformData();
        FbxInterface.GetTransform(pGameObject, ref transform);
         Debug.LogFormat("position {0} {1} {2}", transform.mPosition.mX, transform.mPosition.mY, transform.mPosition.mZ);
         Debug.LogFormat("Rotation {0} {1} {2}", transform.mRotation.mX, transform.mRotation.mY, transform.mRotation.mZ);
         Debug.LogFormat("Scale {0} {1} {2}", transform.mScale.mX, transform.mScale.mY, transform.mScale.mZ);
    }

    static void PrintMesh(IntPtr pGameObject)
    {
        IntPtr pMesh = FbxInterface.GetMesh(pGameObject);
        int polygonCount = FbxInterface.GetPolygonCount(pMesh);
        if (polygonCount == 0)
        {
             Debug.LogFormat("polygonCount：{0}", 0);
        }
        else
        {
            for (int i = 0; i < polygonCount; i++)
            {
                PolygonData polygon = new PolygonData();
                FbxInterface.GetPolygon(pMesh, i, ref polygon);

                 Debug.LogFormat("mMaterialID：{0}", polygon.mMaterialID);
                 Debug.LogFormat("mUVSetCount：{0}", polygon.mUVSetCount);
                 Debug.LogFormat("mCount：{0}", polygon.mCount);

                 Debug.LogFormat("pColors");
                for (int k = 0; k < polygon.mCount; k++)
                {
                     Debug.LogFormat("{0} {1} {2} {3}", polygon.pColors[k].mRed, polygon.pColors[k].mGreen, polygon.pColors[k].mBlue, polygon.pColors[k].mAlpha);
                }
                 Debug.LogFormat("pVertices");
                for (int k = 0; k < polygon.mCount; k++)
                {
                     Debug.LogFormat("{0} {1} {2}", polygon.pVertices[k].mX, polygon.pVertices[k].mY, polygon.pVertices[k].mZ);
                }
                 Debug.LogFormat("pNormals");
                for (int k = 0; k < polygon.mCount; k++)
                {
                     Debug.LogFormat("{0} {1} {2}", polygon.pNormals[k].mX, polygon.pNormals[k].mY, polygon.pNormals[k].mZ);
                }
                 Debug.LogFormat("pTangents");
                for (int k = 0; k < polygon.mCount; k++)
                {
                     Debug.LogFormat("{0} {1} {2}", polygon.pTangents[k].mX, polygon.pTangents[k].mY, polygon.pTangents[k].mZ);
                }
                for (int j = 0; j < polygon.mUVSetCount; j++)
                {
                    if (j == 0)
                    {
                         Debug.LogFormat("pUVS");
                        for (int k = 0; k < polygon.mCount; k++)
                        {
                             Debug.LogFormat("{0} {1}", polygon.pUVS[k].mX, polygon.pUVS[k].mY);
                        }
                    }
                    if (j == 1)
                    {
                         Debug.LogFormat("pUVS2");
                        for (int k = 0; k < polygon.mCount; k++)
                        {
                             Debug.LogFormat("{0} {1}", polygon.pUVS2[k].mX, polygon.pUVS2[k].mY);
                        }
                    }
                    if (j == 2)
                    {
                         Debug.LogFormat("pUVS3");
                        for (int k = 0; k < polygon.mCount; k++)
                        {
                             Debug.LogFormat("{0} {1}", polygon.pUVS3[k].mX, polygon.pUVS3[k].mY);
                        }
                    }
                    if (j == 3)
                    {
                         Debug.LogFormat("pUVS4");
                        for (int k = 0; k < polygon.mCount; k++)
                        {
                             Debug.LogFormat("{0} {1}", polygon.pUVS4[k].mX, polygon.pUVS4[k].mY);
                        }
                    }
                }
            }
        }
    }
    static void PrintRender(IntPtr pGameObject)
    {
        IntPtr render = FbxInterface.GetRender(pGameObject);
        int materialCount = FbxInterface.GetMaterialCount(render);
        if (materialCount == 0)
        {
             Debug.LogFormat("materialCount：{0}", 0);
        }
        else
        {
            for (int i = 0; i < materialCount; i++)
            {
                MaterialData material = new MaterialData();
                FbxInterface.GetMaterial(render, i, ref material);
                 Debug.LogFormat("mShaderType {0}", material.mShaderType);
                 Debug.LogFormat("mAmbient {0} {1} {2} {3}", material.mAmbient.mRed, material.mAmbient.mGreen, material.mAmbient.mBlue, material.mAmbient.mAlpha);
                 Debug.LogFormat("mDiffuse {0} {1} {2} {3}", material.mDiffuse.mRed, material.mDiffuse.mGreen, material.mDiffuse.mBlue, material.mDiffuse.mAlpha);

                if (material.pDiffuseTexture == IntPtr.Zero)
                {
                     Debug.LogFormat("none diffuse texture");
                }
                else
                {
                    TextureData texture = new TextureData();
                    FbxInterface.GetTexture(material.pDiffuseTexture, ref texture);
                    Debug.LogFormat("diffuse texture {0}", texture.mRelativePath);
                }
            }
        }
    }

}
