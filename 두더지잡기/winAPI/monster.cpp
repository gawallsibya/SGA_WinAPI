#include "stdafx.h"
#include "monster.h"

monsterState::monsterState()
{
}
monsterState::~monsterState()
{
}

monsterState::monsterState(STATE state)
{
	this->init(L"ImageResource/monster.bmp", 456, 465, 5, 4, true, RGB(255, 0, 255));
	_state = state;
	_bStop = false;
	_count = 0;
	_secound = 0;

	switch (state)
	{
	case STATE::STATE_NONE:
		this->setFrameX(0);
		this->setFrameY(0);
		break;

	case STATE::STATE_UP:
		this->setFrameX(1);
		this->setFrameY(0);
		break;

	case STATE::STATE_IDLE:
		this->setFrameX(0);
		this->setFrameY(1);
		break;

	case STATE::STATE_DOWN:
		this->setFrameX(4);
		this->setFrameY(0);
		break;

	case STATE::STATE_DAMAGED:
		this->setFrameX(0);
		this->setFrameY(2);
		break;

	case STATE::STATE_DAMAGEDDOWN:
		this->setFrameX(0);
		this->setFrameY(3);
		break;
	default:
		break;
	}
}

const bool monsterState::getIsStop() const
{
	return _bStop;
}

const STATE monsterState::getStateInfo() const
{
	return _state;
}

void monsterState::update(void)
{
	switch (_state)
	{
	case STATE::STATE_NONE:
		_bStop = true;
		break;

	case STATE::STATE_UP:
		_count++;
		//캐릭터 이미지 프레임을 계속 돌려라
		if (_count % 6 == 0)
		{
			this->setFrameX(this->getFrameX() + 1);
			_count = 0;
			if (this->getMaxFrameX() < this->getFrameX() + 1)
			{
				this->setFrameX(1);
				_bStop = true;
			}
		}
		break;

	case STATE::STATE_IDLE:
		_count++;
		//캐릭터 이미지 프레임을 계속 돌려라
		if (_count % 60 == 0)	// 올라오고 1초동안 대기
		{
			_secound++;
			_count = 0;
			if (1 < _secound)
			{
				_secound = 0;
				_bStop = true;
			}
		}
		break;

	case STATE::STATE_DOWN:
		_count++;
		//캐릭터 이미지 프레임을 계속 돌려라
		if (_count % 6 == 0)
		{
			this->setFrameX(this->getFrameX() - 1);
			_count = 0;
			if (1 > this->getFrameX() + 1)
			{
				this->setFrameX(1);
				_bStop = true;
			}
		}
		break;

	case STATE::STATE_DAMAGED:
		_count++;
		//캐릭터 이미지 프레임을 계속 돌려라
		if (_count % 60 == 0)	// 맞으면 1초동안 대기
		{
			_secound++;
			_count = 0;
			if (1 < _secound)
			{
				_secound = 0;
				_bStop = true;
			}
		}
		break;

	case STATE::STATE_DAMAGEDDOWN:
		_count++;
		//캐릭터 이미지 프레임을 계속 돌려라
		if (_count % 6 == 0)
		{
			this->setFrameX(this->getFrameX() + 1);
			_count = 0;
			if (this->getMaxFrameX() < this->getFrameX()+1)
			{
				this->setFrameX(0);
				_bStop = true;
			}
		}
		break;

	default:
		break;
	}
}

monster::monster()
{
	_nowState = nullptr;
}


monster::~monster()
{
}


monsterState* monster::getMyState() const
{
	return _nowState;
}

void monster::changeState(monsterState* state)
{
	if (_nowState == nullptr)
	{
		_nowState = state;
	}
	else
	{
		SAFE_DELETE(_nowState);
		_nowState = state;
	}
}

const RECT monster::boundingBox() const
{
	RECT rc;
	rc = { static_cast<int>(_nowState->getX()),
		static_cast<int>(_nowState->getY()),
		static_cast<int>(_nowState->getX()) + _nowState->getFrameWidth(),
		static_cast<int>(_nowState->getY()) + _nowState->getFrameHeight() };
	
	return rc;
}