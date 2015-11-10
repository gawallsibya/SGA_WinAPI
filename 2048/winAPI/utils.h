#pragma once

#include <cmath>

#define DEG_TO_RAD 0.017453F //degree 1도 (라디안 값)
#define PI 3.1415902654f
#define PI2 (PI * 2)

#define FLOAT_EPSILON 0.001f
#define FLOAT_TO_INT(f1) static_cast<int>(f1 + FLOAT_EPSILON) //실수형을 정수형으로 변환한다
#define FLOAT_EQUAL(f1, f2) (fabs(f1, f2) <= FLOAT_EPSILON) //두 실수가 같냐?

namespace MY_UTIL
{
	//시작점부터 끝점까지의 각을 라디안으로 구한다
	float getAngle(float startX, float startY, float endX, float endY);
	
	//두 점 사이의 거리를 구한다
	float getDistance(float startX, float startY, float endX, float endY);
}

