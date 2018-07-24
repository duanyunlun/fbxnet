#pragma once

#include <fbxsdk.h>
#include<string>



FbxString StdStr2FbxStr(std::string str);
std::string FbxStr2StdStr(FbxString fbxStr);
