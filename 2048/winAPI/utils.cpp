#include "stdafx.h"
#include "utils.h"

namespace MY_UTIL
{
	//시작점부터 끝점까지의 각을 라디안으로 구한다...
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		float d = sqrtf(x * x + y * y);
		float angle = acos(x / d);
		if (y > 0) angle = PI2 - angle;

		return angle;
	}

	//두 점 사이의 거리 구한다
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}
}

