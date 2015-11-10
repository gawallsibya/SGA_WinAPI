#pragma once
#include "image.h"

enum STONECOLOR{ STONE_NONE = 0, STONE_BLACK, STONE_WHITE };

class stone : public image
{
public:
	stone(STONECOLOR stoneColor);
	stone();
	~stone();

private:
	STONECOLOR _stoneColor;

};

