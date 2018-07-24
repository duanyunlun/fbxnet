using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace FbxNet
{
    class Program
    {
        static void Main(string[] args)
        {
            IntPtr pGameObject = FbxInterface.LoadGameObject(@"C:\Users\pengu\Desktop\tianhua\TA0000101.FBX");
            PrintGameObject(pGameObject);
            FbxInterface.Destroy(pGameObject);

            Console.ReadKey();
        }

        static void PrintGameObject(IntPtr pGameObject)
        {
            string name = FbxInterface.GetGameObjectName(pGameObject);
            Console.WriteLine("{0}", name);
            PrintTransform(pGameObject);
            PrintMesh(pGameObject);
            PrintRender(pGameObject);
            int mChildrenCount = FbxInterface.GetChildrenCount(pGameObject);
            Console.WriteLine("mChildrenCount：{0}", 0);
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
            Console.WriteLine("position {0} {1} {2}", transform.mPosition.mX, transform.mPosition.mY, transform.mPosition.mZ);
            Console.WriteLine("Rotation {0} {1} {2}", transform.mRotation.mX, transform.mRotation.mY, transform.mRotation.mZ);
            Console.WriteLine("Scale {0} {1} {2}", transform.mScale.mX, transform.mScale.mY, transform.mScale.mZ);
        }

        static void PrintMesh(IntPtr pGameObject)
        {
            IntPtr pMesh = FbxInterface.GetMesh(pGameObject);
            int polygonCount = FbxInterface.GetPolygonCount(pMesh);
            if (polygonCount == 0)
            {
                Console.WriteLine("polygonCount：{0}", 0);
            }
            else
            {
                for (int i = 0; i < polygonCount; i++)
                {
                    PolygonData polygon = new PolygonData();
                    FbxInterface.GetPolygon(pMesh, i, ref polygon);

                    Console.WriteLine("mMaterialID：{0}", polygon.mMaterialID);
                    Console.WriteLine("mUVSetCount：{0}", polygon.mUVSetCount);
                    Console.WriteLine("mCount：{0}", polygon.mCount);

                    Console.WriteLine("pColors");
                    for (int k = 0; k < polygon.mCount; k++)
                    {
                        Console.WriteLine("{0} {1} {2} {3}", polygon.pColors[k].mRed, polygon.pColors[k].mGreen, polygon.pColors[k].mBlue, polygon.pColors[k].mAlpha);
                    }
                    Console.WriteLine("pVertices");
                    for (int k = 0; k < polygon.mCount; k++)
                    {
                        Console.WriteLine("{0} {1} {2}", polygon.pVertices[k].mX, polygon.pVertices[k].mY, polygon.pVertices[k].mZ);
                    }
                    Console.WriteLine("pNormals");
                    for (int k = 0; k < polygon.mCount; k++)
                    {
                        Console.WriteLine("{0} {1} {2}", polygon.pNormals[k].mX, polygon.pNormals[k].mY, polygon.pNormals[k].mZ);
                    }
                    Console.WriteLine("pTangents");
                    for (int k = 0; k < polygon.mCount; k++)
                    {
                        Console.WriteLine("{0} {1} {2}", polygon.pTangents[k].mX, polygon.pTangents[k].mY, polygon.pTangents[k].mZ);
                    }
                    for (int j = 0; j < polygon.mUVSetCount; j++)
                    {
                        if (j == 0)
                        {
                            Console.WriteLine("pUVS");
                            for (int k = 0; k < polygon.mCount; k++)
                            {
                                Console.WriteLine("{0} {1}", polygon.pUVS[k].mX, polygon.pUVS[k].mY);
                            }
                        }
                        if (j == 1)
                        {
                            Console.WriteLine("pUVS2");
                            for (int k = 0; k < polygon.mCount; k++)
                            {
                                Console.WriteLine("{0} {1}", polygon.pUVS2[k].mX, polygon.pUVS2[k].mY);
                            }
                        }
                        if (j == 2)
                        {
                            Console.WriteLine("pUVS3");
                            for (int k = 0; k < polygon.mCount; k++)
                            {
                                Console.WriteLine("{0} {1}", polygon.pUVS3[k].mX, polygon.pUVS3[k].mY);
                            }
                        }
                        if (j == 3)
                        {
                            Console.WriteLine("pUVS4");
                            for (int k = 0; k < polygon.mCount; k++)
                            {
                                Console.WriteLine("{0} {1}", polygon.pUVS4[k].mX, polygon.pUVS4[k].mY);
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
                Console.WriteLine("materialCount：{0}", 0);
            }
            else
            {
                for (int i = 0; i < materialCount; i++)
                {
                    MaterialData material = new MaterialData();
                    FbxInterface.GetMaterial(render, i, ref material);
                    //Console.WriteLine("material {0}", System.Text.Encoding.Default.GetString(material.mName, 0, material.mNameLength));
                    Console.WriteLine("mShaderType {0}", material.mShaderType);
                    Console.WriteLine("mAmbient {0} {1} {2} {3}", material.mAmbient.mRed, material.mAmbient.mGreen, material.mAmbient.mBlue, material.mAmbient.mAlpha);
                    Console.WriteLine("mDiffuse {0} {1} {2} {3}", material.mDiffuse.mRed, material.mDiffuse.mGreen, material.mDiffuse.mBlue, material.mDiffuse.mAlpha);

                    if (material.pDiffuseTexture == IntPtr.Zero)
                    {
                        Console.WriteLine("none diffuse texture");
                    }
                    else
                    {
                        TextureData texture = new TextureData();
                        FbxInterface.GetTexture(material.pDiffuseTexture, ref texture);
                        string name = texture.mRelativePath;
                        Console.WriteLine("diffuse texture {0}", name);
                    }
                }
            }
        }
    }
}