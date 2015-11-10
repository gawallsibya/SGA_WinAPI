#pragma once

#include "singletonbase.h"
#include <vector>
#include <string>

class txtData : public singletonBase <txtData>
{
public:
	HRESULT init(void);
	void release(void);

	//로드~~~
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);

	//세이브
	void txtSave(const char* saveFileName, vector<string> vStr);
	string vectorArrayCombine(vector<string> vArray);

	txtData(void);
	~txtData(void);
};


