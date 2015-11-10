#pragma once

#include "gameNode.h"
#include <cmath>
#include <vector>

#define MAP_WIDTH_MAX 550
#define MAP_HEIGHT_MAX 475
#define CELL_COUNT 3
#define CELL_WIDTH		MAP_WIDTH_MAX / CELL_COUNT	// 가로 10칸
#define CELL_HEIGHT		MAP_HEIGHT_MAX / CELL_COUNT	// 세로 10칸


class gameStudy : public gameNode
{
public:
	struct cellInfo
	{
		int myIdx = 0;
		int frameX = 0;
		int frameY = 0;

	};

private:
	image* _pMapImage;	//백그라운드 이미지
	image* _endImage;	//끝나는 이미지

	vector<cellInfo*> _vCells;

	//캐릭터 프레임을 돌리기 위한 변수
	int _count;
	int _frameX;
	int _secound;

	bool _bReady;
	bool _bStart;
	bool _bClear;

	// 현재 내 idx
	int _idx;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void changeCell(cellInfo* pCell1, cellInfo* pCell2);
	void initPuzzle();

	bool isClear();

	gameStudy(void);
	~gameStudy(void);
};
