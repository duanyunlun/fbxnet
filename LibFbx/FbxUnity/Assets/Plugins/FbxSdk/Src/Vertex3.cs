using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace UnityEngine.GLEx
{
    /// <summary>
    /// vertex 3D
    /// </summary>
    public class Vertex3
    {
        #region private members

        private Vector3 m_position;
        private Vector2 m_uv;
        private Vector3 m_normal;

        #endregion

        #region public properties

        /// <summary>
        /// get position
        /// </summary>
        public Vector3 Position
        {
            get
            {
                return m_position;
            }
        }

        ///// <summary>
        ///// get uv
        ///// </summary>
        public Vector2 UV
        {
            get
            {
                return m_uv;
            }
        }

        /// <summary>
        /// get normal
        /// </summary>
        public Vector3 Normal
        {
            get
            {
                return m_normal;
            }
        }

        #endregion

        #region constructors

        /// <summary>
        /// constructor
        /// </summary>
        /// <param name="p_position">三维坐标</param>
        /// <param name="p_uv">UV坐标</param>
        public Vertex3(Vector3 p_position, Vector2 p_uv, Vector3 p_normal)
        {
            m_position = p_position;
            m_uv = p_uv;
            m_normal = p_normal;
        }

        #endregion

        #region public functions

        /// <summary>
        /// clone
        /// </summary>
        /// <returns></returns>
        public Vertex3 Clone()
        {
            return new Vertex3(m_position, m_uv, m_normal);
        }

        /// <summary>
        /// interpolate
        /// </summary>
        /// <param name="p_otherVertex">另外点</param>
        /// <param name="p_t">左右比例</param>
        /// <returns>内差点</returns>
        public Vertex3 Interpolate(Vertex3 p_otherVertex, float p_t)
        {
            //Quaternion.Lerp(Quaternion.Euler(this.Normal), Quaternion.Euler(p_otherVertex.Normal), p_t).eulerAngles
            return new Vertex3(Vector3.Lerp(this.Position, p_otherVertex.Position, p_t), Vector2.Lerp(this.UV, p_otherVertex.UV, p_t), Vector3.Lerp(this.Normal, p_otherVertex.Normal, p_t));

            //return new Vertex3D(Vector3.Lerp(this.Position, p_otherVertex.Position, p_t), 
            //    Vector2.Lerp(this.UV, p_otherVertex.UV, p_t), 
            //    Vector3.forward * Quaternion.Lerp(Quaternion.LookRotation(Vector3.forward, this.Normal), Quaternion.FromToRotation(Vector3.forward, p_otherVertex.Normal), p_t).eulerAngles);
        }

        #endregion

        #region object members

        public override bool Equals(object obj)
        {
            if (obj is Vertex3)
            {
                return (obj as Vertex3).Position == this.Position;
            }

            return false;
        }

        public override int GetHashCode()
        {
            return this.Position.GetHashCode();
        }

        #endregion
    }
}
