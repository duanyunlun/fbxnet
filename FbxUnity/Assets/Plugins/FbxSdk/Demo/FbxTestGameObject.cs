using FbxNet;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.GLEx;

public class FbxTestGameObject : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        FbxInterface.Load(@"..\ces.FBX");
    }



}
