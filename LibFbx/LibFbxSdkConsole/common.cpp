#include"common.h"

FbxString StdStr2FbxStr(std::string str)
{
	FbxString retStr = "";
	char * newStr = NULL;
	FbxAnsiToUTF8(str.c_str(), newStr);// Fbx Sdk 提供的字符编码转换API
	if (NULL != newStr)
	{
		retStr = newStr;
		delete[] newStr; // 要记得释放
	}
	return retStr;
}

std::string FbxStr2StdStr(FbxString fbxStr)
{
	std::string retStr = "";
	char * newStr = NULL;
	FbxUTF8ToAnsi(fbxStr.Buffer(), newStr);
	if (NULL != newStr)
	{
		retStr = newStr;
		delete[] newStr;
	}
	return retStr;
}
