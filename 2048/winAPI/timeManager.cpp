#include "stdafx.h"
#include "timeManager.h"

timeManager::timeManager(void) : _timer(nullptr)
{
}

timeManager::~timeManager(void)
{
}

//초기화
HRESULT timeManager::init(void)
{
	//타이머 생성
	_timer = new timer;
	
	//타이머 초기화
	_timer->init();

	return S_OK;
}

//타이머 삭제
void timeManager::release(void)
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
	}
}

//타이머 프레임 적용
void timeManager::update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->tick(lock);
	}
}

//해당 HDC에 정보 찍기
void timeManager::render(HDC hdc)
{
	char str[256];
	std::string strFrame;

	//글자 배경모드 (TRANSPARENT: 투명, QPAQUEL: 불투명)
	SetBkMode(hdc, TRANSPARENT);
	//글자 색상
	SetTextColor(hdc, RGB(0, 0, 0));

#ifdef _DEBUG
	if(_timer != NULL)
	{
		//프레임 찍는다
		sprintf_s(str, "framePerSec : %d", _timer->getFrameRate());
		TextOutA(hdc, 0, 0, str, strlen(str));

		//월드 타임 찍는다(경과시간)
		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOutA(hdc, 0, 20, str, strlen(str));

		//갱신 tick 찍는다
		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOutA(hdc, 0, 40, str, strlen(str));
	}
#else
	if(time != NULL)
	{
		//프레임 찍는다
		sprintf(str, "framePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));		
	}
#endif
}
