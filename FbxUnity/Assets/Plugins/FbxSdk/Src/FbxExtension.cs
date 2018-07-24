using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using UnityEngine.GLEx;

namespace FbxNet
{
    public static class FbxExtension
    {
        public static Vector2 ToVector2(this Vector2Data p_data)
        {
            return new Vector2(p_data.mX, p_data.mY);
        }

        public static void FromVector2(this Vector2Data p_data, Vector2 p_vector)
        {
            p_data.mX = p_vector.x;
            p_data.mY = p_vector.y;
        }

        public static Vector3 ToVector3(this Vector3Data p_data)
        {
            return new Vector3(p_data.mX, p_data.mY, p_data.mZ);
        }

        public static void FromVector3(this Vector3Data p_data, Vector3 p_vector)
        {
            p_data.mX = p_vector.x;
            p_data.mY = p_vector.y;
            p_data.mZ = p_vector.z;
        }

        public static Vector4 ToVector4(this Vector4Data p_data)
        {
            return new Vector4(p_data.mX, p_data.mY, p_data.mZ, p_data.mW);
        }

        public static void FromVector4(this Vector4Data p_data, Vector4 p_vector)
        {
            p_data.mX = p_vector.x;
            p_data.mY = p_vector.y;
            p_data.mZ = p_vector.z;
            p_data.mW = p_vector.w;
        }

        public static Color ToColor(this ColorData p_data)
        {
            return new Color(p_data.mRed, p_data.mGreen, p_data.mBlue, p_data.mAlpha);
        }

        public static void FromColor(this ColorData p_data, Color p_color)
        {
            p_data.mRed = p_color.r;
            p_data.mGreen = p_color.g;
            p_data.mBlue = p_color.b;
            p_data.mAlpha = p_color.a;
        }

        public static Polygon3 ToPolygon(this PolygonData p_data, Matrix4x4 p_matrix)
        {
            Func<Vector3, Vector3> mapVertex = p => new Vector3(-p.x, p.y, p.z);
            Func<Vector2, Vector2> mapUV = p => new Vector2(p.x, p.y);
            List<Vertex3> vertices = new List<Vertex3>();
            for (int i = 0; i < p_data.mCount; i++)
            {
                Vertex3 vertex = new Vertex3(mapVertex(p_matrix.MultiplyPoint3x4(p_data.pVertices[i].ToVector3() / 100)), mapUV(p_data.pUVS[i].ToVector2()), mapVertex(p_data.pNormals[i].ToVector3()));
                vertices.Add(vertex);
            }
            vertices.Reverse();
            Polygon3 polygon = new Polygon3(vertices.ToArray(), p_data.mMaterialID);
            return polygon;
        }

        public static Texture2D GetTexture(this TextureData p_data, string p_directory, bool p_isNormal = false)
        {
            string path = string.Format("{0}\\{1}", p_directory, p_data.mRelativePath);
            byte[] buffer = System.IO.File.ReadAllBytes(path);
            System.IO.FileInfo file = new System.IO.FileInfo(path);
            
            Texture2D texture = new Texture2D(1, 1, TextureFormat.RGB24, true);
            texture.LoadImage(buffer);
            if (p_isNormal)
            {
                return texture.ToNormalMap();
            }
            else
            {
                return texture;
            }
        }

        public static void FromPolygon3(this PolygonData p_data, Polygon3 p_polygon)
        {
            p_data.mCount = p_polygon.Vertices.Count();
            p_data.mUVSetCount = 1;
            for (int i = 0; i < p_data.mCount; i++)
            {
                p_data.pVertices[i].FromVector3(p_polygon.Vertices[i].Position);
                p_data.pUVS[i].FromVector2(p_polygon.Vertices[i].UV);
                p_data.pNormals[i].FromVector3(p_polygon.Vertices[i].Normal);
            }
        }

        public static Material ToMaterial(this MaterialData p_data, string p_directory)
        {
            Material material = new Material(Shader.Find("Standard"));
            material.name = p_data.mName;
            material.SetColor("_Color", p_data.mDiffuse.ToColor());
            if (p_data.pDiffuseTexture != IntPtr.Zero)
            {
                TextureData texture = new TextureData();

                FbxInterface.GetTexture(p_data.pDiffuseTexture, ref texture);
                material.SetTexture("_MainTex", texture.GetTexture(p_directory));
            }

            if (p_data.pNormalTexture != IntPtr.Zero)
            {
                material.EnableKeyword("_NORMALMAP");
                material.SetFloat("_BumpScale", p_data.mBumpFactor);

                TextureData texture = new TextureData();

                FbxInterface.GetTexture(p_data.pNormalTexture, ref texture);
                material.SetTexture("_BumpMap", texture.GetTexture(p_directory, true));
              
            }


            return material;
        }


        public static Texture2D ToNormalMap(this Texture2D p_texture)
        {
            // windows压缩，alpha存储x，r存储y。z通过normalized计算
            if (Application.platform == RuntimePlatform.WindowsEditor || Application.platform == RuntimePlatform.WindowsPlayer)
            {
                Texture2D newTexture = new Texture2D(p_texture.width, p_texture.height, TextureFormat.ARGB32, true);
                Color[] colors = p_texture.GetPixels();
                for (int i = 0; i < colors.Length; i++)
                {
                    Color newColor = new Color();
                    newColor.r = colors[i].r;
                    newColor.b = colors[i].b;
                    newColor.g = colors[i].g;
                    newColor.a = colors[i].r;
                    colors[i] = newColor;
                }
                newTexture.SetPixels(colors);
                newTexture.Apply();
                return newTexture;
            }
            else// 移动端，直接rpg存储normal的方向
            {
                return p_texture;
            }
        }
    }
}
