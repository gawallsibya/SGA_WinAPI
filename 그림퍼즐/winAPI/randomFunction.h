#pragma once

#include "singletonBase.h"
#include <time.h>

//=========================================================
// 2014.10.22 ## commonMacroFunction ## -Wednesday Of Blood
//=========================================================

class randomFunction : public singletonBase <randomFunction>
{
public:
	randomFunction(void)
	{
		srand(GetTickCount());
	}
	~randomFunction(void)
	{
	}

	//getInt
	inline int getInt(int num) {return rand() % num;}
	inline int getFromIntTo(int fromNum, int toNum) {return (rand() % (toNum - fromNum + 1)) + fromNum;}
	
	//getFloat
	inline float getFloat(float num) {return ((float)rand() / (float)RAND_MAX) * num;}
	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum); 
	}
	
};