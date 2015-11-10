#pragma once
#include "block.h"
#include "unit.h"
#include <list>
#include <vector>

class stage
{
private:
	#define BLOCK_WIDTH 4
	#define BLOCK_HEIGHT 4

public:
	stage();
	~stage();

	void init();
	void update();
	void render(HDC hdc);
	void release();

private:
	void commendUpdate();
	bool isUnitHandling(block* prevBlock, block* nextBlock);
	void RndCreateUnit();

private:
	block _block[BLOCK_HEIGHT][BLOCK_WIDTH];
	list<unit*> lUnitList;
	vector<block*> vNullBlockList;
	int _unitCount;
};

