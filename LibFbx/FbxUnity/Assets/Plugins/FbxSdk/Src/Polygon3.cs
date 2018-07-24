using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace UnityEngine.GLEx
{
    public class Polygon3
    {
        #region private members

        private int m_materialID;
        private Plane m_plane;
        private Vertex3[] m_vertices;

        #endregion

        #region public properties

        /// <summary>
        /// get material id
        /// </summary>
        public int MaterialID
        {
            get
            {
                return m_materialID;
            }
        }

        /// <summary>
        /// get plane
        /// </summary>
        public UnityEngine.Plane Plane
        {
            get
            {
                return m_plane;
            }
        }

        /// <summary>
        /// get vertices
        /// </summary>
        public Vertex3[] Vertices
        {
            get
            {
                return m_vertices.ToArray();
            }
        }

        #endregion

        #region constructors

        /// <summary>
        /// constructor
        /// </summary>
        /// <param name="p_vertices">顶点集</param>
        /// <param name="p_objID">物体ID</param>
        /// <param name="p_materialID">材质ID</param>
        /// <remarks>参数顶点集，三个顶点顺序，右手螺旋决定法线方向</remarks>
        public Polygon3(Vertex3[] p_vertices, int p_materialID)
        {
            m_materialID = p_materialID;

            m_vertices = p_vertices;
            m_plane = new Plane(m_vertices[0].Position, m_vertices[1].Position, m_vertices[2].Position);

            if (m_plane.normal == Vector3.zero)
            {
                Vector3 temp0 = (m_vertices[1].Position - m_vertices[0].Position) * 1000;
                Vector3 temp1 = (m_vertices[2].Position - m_vertices[0].Position) * 1000;
                Vector3 normal = Vector3.Cross(temp0, temp1).normalized;
                m_plane.normal = normal;
            }
            // 找到凸点，利用凸包的概念，然后以凸点的上一个点作为起点，保证该点不是凹点
            //int index = -1;
            //for (int i = 0; i < p_vertices.Count(); i++)
            //{
            //    if (index == -1)
            //    {
            //        index = 0;
            //    }
            //    else
            //    {
            //        if (p_vertices[i].Position.x < p_vertices[index].Position.x)
            //        {
            //            index = i;
            //        }
            //        else if (p_vertices[i].Position.x == p_vertices[index].Position.x)
            //        {
            //            if (p_vertices[i].Position.y < p_vertices[index].Position.y)
            //            {
            //                index = i;
            //            }
            //            else if (p_vertices[i].Position.y == p_vertices[index].Position.y)
            //            {
            //                if (p_vertices[i].Position.z < p_vertices[index].Position.z)
            //                {
            //                    index = i;
            //                }
            //            }
            //        }
            //    }
            //}
            //m_plane = new Plane(p_vertices[(index - 1 + p_vertices.Length) % p_vertices.Length].Position, p_vertices[index].Position, p_vertices[(index + 1) % p_vertices.Length].Position);
            //m_vertices = p_vertices.Skip((index - 1 + p_vertices.Length) % p_vertices.Length).Concat(p_vertices.Take((index - 1 + p_vertices.Length) % p_vertices.Length)).ToArray();
        }

        /// <summary>
        /// constructor
        /// </summary>
        /// <param name="p_vertex1">顶点1</param>
        /// <param name="p_vertex2">顶点2</param>
        /// <param name="p_vertex3">顶点3</param>
        /// <param name="p_objID">物体ID</param>
        /// <param name="p_materialID">材质ID</param>
        /// <remarks>参数顶点集，三个顶点顺序，右手螺旋决定法线方向</remarks>
        public Polygon3(Vertex3 p_vertex1, Vertex3 p_vertex2, Vertex3 p_vertex3, int p_materialID)
        {
            m_plane = new UnityEngine.Plane(p_vertex1.Position, p_vertex2.Position, p_vertex3.Position);
            this.m_vertices = new Vertex3[] { p_vertex1, p_vertex2, p_vertex3 };
            this.m_materialID = p_materialID;
        }

        #endregion

        #region public functions

        /// <summary>
        /// clone
        /// </summary>
        /// <returns></returns>
        public Polygon3 Clone()
        {
            return new Polygon3(this.Vertices, this.MaterialID);
        }

        /// <summary>
        /// flip face normal
        /// </summary>
        /// <returns></returns>
        public Polygon3 Flip()
        {
            return new Polygon3((from a in this.Vertices select a).Reverse<Vertex3>().ToArray(), this.MaterialID);
        }

        /// <summary>
        ///  convex-polygonize
        /// </summary>
        public List<Polygon3> ConvexPolygonize()
        {
            // 顶点退化检查，如果有顶点需要退化，则退化顶点
            VertexDegenerate();

            // 顶点小于3，则直接退化掉
            if (Vertices.Length < 3)
            {
                return new List<Polygon3>();
            }

            // 多边形临时寄存器
            List<Polygon3> res = new List<Polygon3>();
            res.Add(this);

            for (int i = 0; i < Vertices.Length; i++)
            {
                Vertex3 pre = Vertices[(i - 1 + Vertices.Length) % Vertices.Length];            // A
                Vertex3 curr = Vertices[i];                                                     // B
                Vertex3 next = Vertices[(i + 1) % Vertices.Length];                             // C

                Plane plane = new Plane(pre.Position, curr.Position, next.Position);
                //  法线方向相反，则当前点为凹点
                if (plane.normal.normalized != m_plane.normal.normalized)
                {
                    // 寻找到拐点，然后切掉一个三角形，剩下的继续作为一个闭合的多边形进行处理，直到找不到拐点。此处注意的是切掉的是拐点的上一个顶点作为中间点的三角形。
                    res.Remove(this);
                    Polygon3 polygonFirst = new Polygon3(Vertices[(i - 2 + Vertices.Length) % Vertices.Length], Vertices[(i - 1 + Vertices.Length) % Vertices.Length], Vertices[i], m_materialID);
                    res.Add(polygonFirst);

                    List<Vertex3> verticesArray = new List<Vertex3>(Vertices);
                    verticesArray.RemoveAt((i - 1 + Vertices.Length) % Vertices.Length);
                    if (verticesArray.Count >= 3)// 此处的if判断只是为了逻辑的严谨，严格来说不会出现else的情形，因为三角形不可能是凹多边形，所以不存在减少一个点变成小于3个顶点的情形。
                    {
                        Polygon3 polygonSecond = new Polygon3(verticesArray.ToArray(), m_materialID);
                        polygonSecond.m_plane = m_plane;
                        res.AddRange(polygonSecond.ConvexPolygonize());
                    }
                    break;
                }
            }
            return res;
        }

        /// <summary>
        /// vertices degenerate
        /// </summary>
        public void VertexDegenerate()
        {
            List<Vertex3> vertices = new List<Vertex3>(m_vertices);
            if (vertices.Count >= 3)
            {
                for (int i = 0; i < vertices.Count; i++)
                {
                    Vertex3 pre = vertices[(i - 1 + vertices.Count) % vertices.Count];
                    Vertex3 curr = vertices[i];
                    Vertex3 next = vertices[(i + 1) % vertices.Count];
                    if ((next.Position - curr.Position).normalized == (curr.Position - pre.Position).normalized)//在一条直线上
                    {
                        vertices.RemoveAt(i);
                        i--;
                    }
                }
            }
            m_vertices = vertices.ToArray();
        }

        /// <summary>
        /// ring belt cut
        /// </summary>
        /// <param name="p_remove"></param>
        public List<Vertex3> RingBeltCut(List<Vertex3> p_remove)
        {
            // 顶点列表首尾相连，即复制一份，空间换时间，省去取模的操作
            List<Vertex3> vertices = new List<Vertex3>(m_vertices);
            vertices = vertices.Concat(m_vertices).ToList();

            // 开始寻找起始点，找到了，则开始添加到新的集合中，直到找到结束点，结束
            // 需要注意的是起始点和结束点都需要添加到结果集
            List<Vertex3> res = new List<Vertex3>();
            bool findStart = false;
            bool findEnd = false;
            for (int i = 0; i < vertices.Count; i++)
            {
                if (vertices[i].Equals(p_remove.Last()))
                {
                    findStart = true;
                }

                if (findStart)
                {
                    if (vertices[i].Equals(p_remove.First()))
                    {
                        findEnd = true;
                    }
                }

                if (findStart)
                {
                    res.Add(vertices[i]);
                }

                if (findEnd)
                {
                    break;
                }
            }
            return res;
        }

        /// <summary>
        /// split polygon
        /// </summary>
        /// <returns></returns>
        public List<Polygon3> Split()// 多边形拆分，将闭合的多边形拆分开
        {
            List<Vertex3> vertices = new List<Vertex3>(m_vertices);
            List<Polygon3> res = new List<Polygon3>();
            for (int i = 0; i < vertices.Count - 1; i++)
            {
                for (int j = i + 1; j < vertices.Count; j++)
                {
                    if (vertices[i].Position == vertices[j].Position)
                    {
                        if (j == i + 1)// 相邻的两个点的坐标相同，则移除一个
                        {
                            vertices.RemoveAt(j);
                            j--;
                        }
                        else
                        {
                            // 内环作为一个单独的多边形
                            Polygon3 polygon = new Polygon3(vertices.Skip(i).Take(j - i).ToArray(), m_materialID);
                            polygon.m_plane = m_plane;
                            res.Add(polygon);
                            vertices = vertices.Take(i).Concat(vertices.Skip(j + 1)).ToList();
                        }
                    }
                }
            }
            if (vertices.Count > 2)
            {
                Polygon3 polygon = new Polygon3(vertices.ToArray(), m_materialID);
                polygon.m_plane = m_plane;
                res.Add(polygon);
            }

            return res;
        }

        #endregion

        #region public static functions

        /// <summary>
        /// is degenrate set
        /// </summary>
        /// <param name="p_vertecs">多边形顶点集合</param>
        /// <returns></returns>
        public static bool IsDegenerateSet(IEnumerable<Vertex3> p_vertecs)
        {
            // 传入的多边形顶点集合为空或者大小小于3，则退化
            if (p_vertecs == null || p_vertecs.Count<Vertex3>() < 3)
            {
                return true;
            }

            // 顶点塌陷之后，如果低于三个点，则表示该面需要退化
            return ((from a in p_vertecs group a by a.Position into aa select aa.First<Vertex3>()).Count<Vertex3>() < 3);
        }

        ///// <summary>
        ///// whether has neighbor vertices or not
        ///// </summary>
        ///// <param name="p_polygonLeft">左操作数</param>
        ///// <param name="p_polygonRight">右操作数</param>
        ///// <param name="p_vertices">输出参数，重合顶点集，其排列顺序为左操作数中点排列顺序</param>
        ///// <returns>是否为相邻的多边形</returns>
        //public static bool HasNeighborVertices(Polygon3D p_polygonLeft, Polygon3D p_polygonRight, out List<Vertex3D> p_vertices)
        //{
        //    if (p_polygonLeft.m_plane.normal.normalized != p_polygonRight.m_plane.normal.normalized)
        //    {
        //        p_vertices = null;
        //        return false;
        //    }

        //    List<Vertex3D> verticesLeft = p_polygonLeft.Vertices.ToList();
        //    List<Vertex3D> verticseRight = p_polygonRight.Vertices.ToList();
        //    verticseRight.Reverse();

        //    for (int i = 0; i < verticesLeft.Count; i++)
        //    {
        //        for (int j = 0; j < verticseRight.Count; j++)
        //        {
        //            if (verticesLeft[i].Position == verticseRight[j].Position)
        //            {
        //                List<Vertex3D> vertices = new List<Vertex3D>();
        //                int tmp = 0;
        //                while (true)
        //                {
        //                    if (i + tmp >= verticesLeft.Count)
        //                    {
        //                        break;
        //                    }

        //                    if (verticesLeft[(i + tmp) % verticesLeft.Count].Position == verticseRight[(j + tmp) % verticseRight.Count].Position)
        //                    {
        //                        vertices.Add(verticesLeft[(i + tmp) % verticesLeft.Count]);
        //                    }
        //                    else
        //                    {
        //                        break;
        //                    }
        //                    tmp++;
        //                }
        //                if (vertices.Count >= 2)
        //                {
        //                    p_vertices = vertices;
        //                    return true;
        //                }
        //            }
        //        }
        //    }
        //    p_vertices = null;
        //    return false;
        //}

        ///// <summary>
        ///// combine polygon
        ///// </summary>
        ///// <param name="p_polygons"></param>
        ///// <returns></returns>
        //public static List<Polygon3D> PolygonDegenerateInPlane(IEnumerable<Polygon3D> p_polygons, Plane p_splitPlane)
        //{
        //    // 参数检查
        //    if (p_polygons == null || p_polygons.Count() == 0)
        //    {
        //        return new List<Polygon3D>(p_polygons);
        //    }

        //    List<Polygon3D> polygons = new List<Polygon3D>(p_polygons);
        //    // 删除非法的多边形
        //    for (int i = 0; i < polygons.Count; i++)
        //    {
        //        // 点退化的多边形直接移除（所有点在一条直线上，无法形成多边形）
        //        if (Polygon3D.IsDegenerateSet(polygons[i].Vertices))
        //        {
        //            polygons.RemoveAt(i);
        //            i--;
        //        }

        //        //// 反向的多边形，直接移除
        //        //if (polygons[i].Plane.normal.normalized != p_splitPlane.normal.normalized)
        //        //{
        //        //    polygons.RemoveAt(i);
        //        //    i--;
        //        //}
        //    }

        //    // 1、合并相邻多边形
        //    // 2、多边形退化
        //    for (int i = 0; i < polygons.Count; i++)
        //    {
        //        Polygon3D polygonLeft = polygons[i];                                                         // 左操作数
        //        Polygon3D polygonRight = null;                                                               // 右操作数
        //        List<Vertex3D> neighborVertices = new List<Vertex3D>();                                       // 相邻顶点

        //        // 遍历寻找相邻的多边形
        //        foreach (var item in polygons)
        //        {
        //            if (item != polygons[i])
        //            {
        //                if (Polygon3D.HasNeighborVertices(polygonLeft, item, out neighborVertices))          // 判断是否相邻，并计算相邻顶点集
        //                {
        //                    polygonRight = item;
        //                    break;
        //                }
        //            }
        //        }

        //        // 找到相邻的多边形，合并
        //        if (polygonRight != null)
        //        {
        //            Polygon3D polygon = Polygon3D.CombinePolygon(polygonLeft, polygonRight, neighborVertices);
        //            polygons.Remove(polygonLeft);
        //            polygons.Remove(polygonRight);
        //            polygons.Add(polygon);
        //            i = -1;
        //        }
        //    }

        //    //// 凹多边形处理
        //    //List<Polygon> polygonsTemp = new List<Polygon>();
        //    //for (int i = 0; i < polygons.Count; i++)
        //    //{
        //    //    polygonsTemp.AddRange(poly gons[i].ConvexPolygonize());
        //    //}
        //    //polygons = polygonsTemp;

        //    //// 多边形点退化
        //    //for (int i = 0; i < polygons.Count; i++)
        //    //{
        //    //    polygons[i].VertexDegenerate();
        //    //}

        //    //for (int i = 0; i < polygons.Count; i++)
        //    //{
        //    //    // 点退化的多边形直接移除（所有点在一条直线上，无法形成多边形）
        //    //    if (Polygon.IsDegenerateSet(polygons[i].Vertices))
        //    //    {
        //    //        polygons.RemoveAt(i);
        //    //        i--;
        //    //    }

        //    //    // 反向的多边形，直接移除
        //    //    if (polygons[i].Plane.normal.normalized == -p_splitPlane.normal.normalized)
        //    //    {
        //    //        polygons.RemoveAt(i);
        //    //        i--;
        //    //    }
        //    //}

        //    return polygons;
        //}

        ///// <summary>
        ///// combine polygon
        ///// </summary>
        ///// <param name="p_polygonLeft">左操作数</param>
        ///// <param name="p_polygonRight">右操作树</param>
        ///// <param name="p_vertices">相邻点</param>
        ///// <returns>合并后的多边形</returns>
        //public static Polygon3D CombinePolygon(Polygon3D p_polygonLeft, Polygon3D p_polygonRight, List<Vertex3D> p_vertices)
        //{
        //    List<Vertex3D> left = p_polygonLeft.RingBeltCut(p_vertices);
        //    p_vertices.Reverse();
        //    List<Vertex3D> right = p_polygonRight.RingBeltCut(p_vertices);
        //    if (right.Count >= 3)
        //    {
        //        right.RemoveAt(0);
        //        right.RemoveAt(right.Count - 1);
        //    }

        //    List<Vertex3D> vertices = left.Concat(right).ToList();
        //    return new Polygon3D(vertices.ToArray(), p_polygonLeft.MaterialID);
        //}

        /// <summary>
        /// generate mesh
        /// </summary>
        /// <param name="p_polygons">多边形集</param>
        /// <returns>网格</returns>
        public static Mesh GenerateMesh(IEnumerable<Polygon3> p_polygons)
        {
            // 参数检查
            if (p_polygons == null || p_polygons.Count() == 0)
            {
                return null;
            }

            List<Vector3> vertices = new List<Vector3>();                                                                                   // 顶点
            List<Vector2> uvs = new List<Vector2>();                                                                                        // UV坐标
            List<Vector3> normals = new List<Vector3>();
            List<int>[] submeshes = new List<int>[1024];                                                                                    // 子网格
            int subMeshCount = 0;                                                                                                           // 子网格数量

            foreach (var polygon in p_polygons)
            {
                Func<Vertex3, int> funVertex2Int = a =>
                {
                    vertices.Add(a.Position);                                                                                               // 添加顶点
                    uvs.Add(a.UV);                                                                                                          // 添加UV坐标
                    normals.Add(a.Normal);
                    return vertices.Count - 1;
                };

                int[] localArray = Enumerable.Select<Vertex3, int>(polygon.Vertices, funVertex2Int).ToArray();
                for (int i = 2; i < localArray.Length; i++)
                {
                    if (submeshes[polygon.MaterialID] == null)
                    {
                        submeshes[polygon.MaterialID] = new List<int>(100);
                        subMeshCount++;                                                                                                     // 子网格计数
                    }
                    submeshes[polygon.MaterialID].Add(localArray[0]);
                    submeshes[polygon.MaterialID].Add(localArray[i - 1]);
                    submeshes[polygon.MaterialID].Add(localArray[i]);
                }
            }

            Mesh sharedMesh = new Mesh();
            sharedMesh.vertices = vertices.ToArray();
            sharedMesh.normals = normals.ToArray();
            sharedMesh.subMeshCount = subMeshCount;
            int submeshIndex = 0;                                                                                                           // 子网格索引
            for (int i = 0; i < submeshes.Length; i++)
            {
                List<int> subMeshTriangles = submeshes[i];
                if ((subMeshTriangles != null) && (subMeshTriangles.Count > 0))
                {
                    sharedMesh.SetTriangles(subMeshTriangles.ToArray(), submeshIndex);                                                      // 设置子网格
                    submeshIndex++;
                }
            }
            sharedMesh.uv = uvs.ToArray();
            sharedMesh.RecalculateNormals();                                                                                                // 重计算法线
            sharedMesh.RecalculateBounds();                                                                                                 // 重计算边界

            return sharedMesh;
        }

        /// <summary>
        /// generate GameObject
        /// </summary>
        /// <param name="p_polygos">多边形集</param>
        /// <param name="p_material">材质集</param>
        /// <returns></returns>
        public static GameObject GenerateObject(IEnumerable<Polygon3> p_polygos, IEnumerable<Material> p_material, bool p_isAddColider = true)
        {
            List<int> materialids = new List<int>();
            foreach (var item in p_polygos)
            {
                materialids.Add(item.MaterialID);
            }
            materialids = materialids.Distinct().ToList();
            materialids.Sort();
            List<Material> materials = p_material.ToList();

            GameObject gObject = new GameObject();
            MeshFilter meshfilter = gObject.AddComponent<MeshFilter>();
            meshfilter.sharedMesh = Polygon3.GenerateMesh(p_polygos);
            MeshRenderer renderer = gObject.AddComponent<MeshRenderer>();
            renderer.materials = materialids.Select(p => materials[p]).ToArray();

            if (p_isAddColider)                                                                                             // 碰撞器
            {
                MeshCollider meshCollider = gObject.AddComponent<MeshCollider>();
                meshCollider.sharedMesh = meshfilter.sharedMesh;
            }

            return gObject;
        }

        #endregion
    }

}
