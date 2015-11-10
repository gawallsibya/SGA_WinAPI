#include "stdafx.h"
#include "animation.h"

animation::animation(void)
:_frameNum(0),
_frameWidth(0),
_frameHeight(0),
_loop(false),
_frameUpdateSec(0),
_elapsedSec(0),
_nowPlayIdx(0),
_play(false)
{
}

animation::~animation(void)
{
}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//가로 프레임 수..
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	//세로 프레임 수
	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	//총 프레임 수 계산한다
	_frameNum = _frameNumWidth * _frameNumHeight;

	//프레임 위치 리스트 셋팅해준다
	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_vFrameList.push_back(framePos);
		}
	}

	//기본 프레임 셋팅
	setDefPlayFrame();

	return S_OK;
}

//기본 셋팅 애니메이션ㅋ~
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//루프냐?
	_loop = loop;

	//플레이 리스트 클리어
	_vPlayList.clear();

	//다시 되돌아오냐?
	if (reverse)
	{
		if (_loop)
		{
			//프레임 Go~
			for (int i = 0; i < _frameNum; i++)
			{
				_vPlayList.push_back(i);
			}

			//프레임 back~
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_vPlayList.push_back(i);
			}
		}
		else
		{
			//프레임 Go~
			for (int i = 0; i < _frameNum; i++)
			{
				_vPlayList.push_back(i);
			}

			//프레임 back~
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_vPlayList.push_back(i);
			}
		}
	}
	else 
	{
		//프레임 Go~
		for (int i = 0; i < _frameNum; i++)
		{
			_vPlayList.push_back(i);
		}
	}
}

//배열로 셋팅 애니메이션
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	_loop = loop;

	_vPlayList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_vPlayList.push_back(playArr[i]);
	}
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_loop = loop;

	_vPlayList.clear();

	if (start == end)
	{
		//시작 프레임과 끝프레임이 같으면~~~
		_vPlayList.clear();
		stop();
		return;
	}

	//시작이 종료보다 크면..
	if (start > end)
	{
		//되돌아오냐?
		if (reverse)
		{
			//루프냐?
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_vPlayList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_vPlayList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_vPlayList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i >= end; i--)
			{
				_vPlayList.push_back(i);
			}
		}
	}
	else
	{
		//되돌아오냐?
		if (reverse)
		{
			//루프냐?
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_vPlayList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_vPlayList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_vPlayList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i++)
			{
				_vPlayList.push_back(i);
			}
		}
	}
}

//초당 갱신 횟수
void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

//프레임 업데이트
void animation::frameUpdate(float elpasedTime)
{
	if (_play)
	{
		_elapsedSec += elpasedTime;

		//프레임 업데이트 시간이 다 되었으면...
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec = 0.0f;
			_nowPlayIdx++;
			if (_nowPlayIdx == _vPlayList.size())
			{
				//루프냐?
				if (_loop)
				{
					_nowPlayIdx = 0;
				}
				else
				{
					_nowPlayIdx--;
					_play = false;
				}
			}
		}
	}
}

//플레이 시작..
void animation::start(void)
{
	_play = true;
	_nowPlayIdx = 0;
}

//정지
void animation::stop(void)
{
	_play = false;
	_nowPlayIdx = 0;
}

//일시정지..
void animation::pause(void)
{
	_play = false;
}

//다시 시작..
void animation::resume(void)
{
	_play = true;
}

