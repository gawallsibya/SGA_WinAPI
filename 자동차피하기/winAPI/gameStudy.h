#pragma once

#include "gameNode.h"
#include <cmath>
#include <vector>

#define MAP_WIDTH_MAX 550
#define MAP_HEIGHT_MAX 475
#define CELL_COUNT 10
#define CELL_WIDTH		MAP_WIDTH_MAX / CELL_COUNT	// ���� 10ĭ
#define CELL_HEIGHT		MAP_HEIGHT_MAX / CELL_COUNT	// ���� 10ĭ



class gameStudy : public gameNode
{
public:

private:
	image* _pBackgoundImage1;	//��׶��� �̹���
	image* _pBackgoundImage2;	//��׶��� �̹���

	image* _pPlayerImage;
	image* _pEnemyImages;
	
	float* fArrEnemyY;

	image* _endImage;	//������ �̹���


	//ĳ���� �������� ������ ���� ����
	int _count;
	int _frameX;
	int _secound;

	int _nPlayerMoveSpeed;

	float _fSpeed;
	float _fSpeedMax;

	float _fEnemySpeed;

	bool _bGameOver;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	bool isCollisionMap(RECT rt);
	bool isCollisionRect(RECT rt1, RECT rt2);
	gameStudy(void);
	~gameStudy(void);
};
