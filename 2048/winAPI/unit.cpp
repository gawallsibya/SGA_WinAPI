#include "stdafx.h"
#include "unit.h"
#include "block.h"

unit::unit() : _number(0), _myBlock(nullptr)
{
}


unit::~unit()
{
}

void unit::init(int x, int y, int width, int height)
{
	_img = IMAGEMANAGER->findImage("block");

	_x = x;
	_y = y;
	_width = width;
	_height = height;

	_speed = 5000;
}
void unit::render(HDC hdc)
{
	if (_number != 0)
	{
		_img->frameRender(hdc, _x, _y, _frameX, 0);
	}
}
void unit::update()
{
	if (_myBlock->getPos().x != _x)
	{
		if (_myBlock->getPos().x - _x > 0)
		{
			_x += _speed * TIMEMANAGER->getElapsedTime();
			if (_myBlock->getPos().x < _x)
			{
				_x = _myBlock->getPos().x;
			}

		}
		else if (_myBlock->getPos().x - _x < 0)
		{
			_x -= _speed * TIMEMANAGER->getElapsedTime();
			if (_myBlock->getPos().x > _x)
			{
				_x = _myBlock->getPos().x;
			}
		}
	}
	if (_myBlock->getPos().y != _y)
	{
		if (_myBlock->getPos().y - _y > 0)
		{
			_y += _speed * TIMEMANAGER->getElapsedTime();
			if (_myBlock->getPos().y < _y)
			{
				_y = _myBlock->getPos().y;
			}
		}
		else if (_myBlock->getPos().y - _y < 0)
		{
			_y -= _speed * TIMEMANAGER->getElapsedTime();
			if (_myBlock->getPos().y > _y)
			{
				_y = _myBlock->getPos().y;
			}
		}
	}
}
void unit::release()
{
}
//------------

void unit::setRndNumber()
{
	int rnd = RND->getInt(10);
	if (rnd != 9)
	{
		setNumber(2);
	}
	else if (rnd == 9)
	{
		setNumber(4);
	}
}

void unit::setPos(int x, int y)
{
	_x = x;
	_y = y;
}

POINT unit::getPos()
{
	POINT p = { _x, _y };
	return p;
}


void unit::setNumber(int num)
{
	_number = num;

	switch (_number)
	{
	case 0:
		_frameX = -1;
		break;
	case 2:
		_frameX = 0;
		break;
	case 4:
		_frameX = 1;
		break;
	case 8:
		_frameX = 2;
		break;
	case 16:
		_frameX = 3;
		break;
	case 32:
		_frameX = 4;
		break;
	case 64:
		_frameX = 5;
		break;
	case 128:
		_frameX = 6;
		break;
	case 256:
		_frameX = 7;
		break;
	case 512:
		_frameX = 8;
		break;
	case 1024:
		_frameX = 9;
		break;
	case 2048:
		_frameX = 10;
		break;
	default:
		break;
	}
}

int unit::getNumber()
{
	return _number;
}

void unit::setMyBlock(block* myBlock)
{
	_myBlock = myBlock;
}

block* unit::getMyBlock()
{
	return _myBlock;
}