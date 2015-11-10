#include "stdafx.h"
#include "stone.h"


stone::stone()
{
}

stone::stone(STONECOLOR stoneColor)
{
	switch (stoneColor)
	{
	case STONECOLOR::STONE_BLACK:
		this->init(L"ImageResource/stone_black.bmp", 27, 27, true, RGB(255, 0, 255));
		break;
	case STONECOLOR::STONE_WHITE:
		this->init(L"ImageResource/stone_white.bmp", 27, 27, true, RGB(255, 0, 255));
		break;
	default:
		break;
	}

	_stoneColor = stoneColor;
}

stone::~stone()
{
}
