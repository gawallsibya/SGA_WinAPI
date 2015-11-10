#pragma once

#include "gameNode.h"
#include <cmath>
#include <vector>

#define MAP_WIDTH_MAX 550
#define MAP_HEIGHT_MAX 475
#define CELL_COUNT 3
#define CELL_WIDTH		MAP_WIDTH_MAX / CELL_COUNT	// ���� 10ĭ
#define CELL_HEIGHT		MAP_HEIGHT_MAX / CELL_COUNT	// ���� 10ĭ


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
	image* _pMapImage;	//��׶��� �̹���
	image* _endImage;	//������ �̹���

	vector<cellInfo*> _vCells;

	//ĳ���� �������� ������ ���� ����
	int _count;
	int _frameX;
	int _secound;

	bool _bReady;
	bool _bStart;
	bool _bClear;

	// ���� �� idx
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
