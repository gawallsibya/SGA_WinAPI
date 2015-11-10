#include "stdafx.h"
#include "txtData.h"

txtData::txtData(void)
{
}

txtData::~txtData(void)
{
}

HRESULT txtData::init(void)
{
	return S_OK;
}

void txtData::release(void)
{
	
}

//로드~~~
vector<string> txtData::txtLoad(const char* loadFileName)
{
	HANDLE file;
	char str[128];
	DWORD read;

	memset(str, 0, 128);
	file = CreateFileA(loadFileName, 
		GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* nextContext = nullptr;
	char* separator = ",";
	char* token;

	token = strtok_s(charArray, separator, &nextContext);
	vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &nextContext)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

//세이브
void txtData::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;
	//char str[128];
	string str;
	DWORD write;

	str = vectorArrayCombine(vStr);
	//strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFileA(saveFileName, 
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str.c_str(), str.size(), &write, NULL);
	CloseHandle(file);
}

string txtData::vectorArrayCombine(vector<string> vArray)
{
	//char str[128];
	string str;
	str.clear();
	//ZeroMemory(str, sizeof(str));

	for (unsigned int i = 0; i < vArray.size(); i++)
	{
		str += vArray[i];
		//strncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray.size()) str += ",";//strcat_s(str, ",");
	}
	return str;
}

