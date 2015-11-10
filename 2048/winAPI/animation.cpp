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
	//���� ������ ��..
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	//���� ������ ��
	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	//�� ������ �� ����Ѵ�
	_frameNum = _frameNumWidth * _frameNumHeight;

	//������ ��ġ ����Ʈ �������ش�
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

	//�⺻ ������ ����
	setDefPlayFrame();

	return S_OK;
}

//�⺻ ���� �ִϸ��̼Ǥ�~
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//������?
	_loop = loop;

	//�÷��� ����Ʈ Ŭ����
	_vPlayList.clear();

	//�ٽ� �ǵ��ƿ���?
	if (reverse)
	{
		if (_loop)
		{
			//������ Go~
			for (int i = 0; i < _frameNum; i++)
			{
				_vPlayList.push_back(i);
			}

			//������ back~
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_vPlayList.push_back(i);
			}
		}
		else
		{
			//������ Go~
			for (int i = 0; i < _frameNum; i++)
			{
				_vPlayList.push_back(i);
			}

			//������ back~
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_vPlayList.push_back(i);
			}
		}
	}
	else 
	{
		//������ Go~
		for (int i = 0; i < _frameNum; i++)
		{
			_vPlayList.push_back(i);
		}
	}
}

//�迭�� ���� �ִϸ��̼�
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
		//���� �����Ӱ� ���������� ������~~~
		_vPlayList.clear();
		stop();
		return;
	}

	//������ ���Ẹ�� ũ��..
	if (start > end)
	{
		//�ǵ��ƿ���?
		if (reverse)
		{
			//������?
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
		//�ǵ��ƿ���?
		if (reverse)
		{
			//������?
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

//�ʴ� ���� Ƚ��
void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

//������ ������Ʈ
void animation::frameUpdate(float elpasedTime)
{
	if (_play)
	{
		_elapsedSec += elpasedTime;

		//������ ������Ʈ �ð��� �� �Ǿ�����...
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec = 0.0f;
			_nowPlayIdx++;
			if (_nowPlayIdx == _vPlayList.size())
			{
				//������?
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

//�÷��� ����..
void animation::start(void)
{
	_play = true;
	_nowPlayIdx = 0;
}

//����
void animation::stop(void)
{
	_play = false;
	_nowPlayIdx = 0;
}

//�Ͻ�����..
void animation::pause(void)
{
	_play = false;
}

//�ٽ� ����..
void animation::resume(void)
{
	_play = true;
}

