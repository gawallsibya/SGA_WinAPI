#include "stdafx.h"
#include "block.h"
#include "unit.h"

block::block() : _unit(nullptr), _x(0), _y(0), _width(0), _height(0), _idxX(0), _idxY(0)
{
}

block::~block()
{
}

void block::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}
void block::render(HDC hdc)
{
	Rectangle(hdc, _x, _y, _x + _width, _y + _height);
}
void block::update()
{
}
void block::release()
{
}

void block::deleteUnit() 
{
	SAFE_DELETE(_unit);
}