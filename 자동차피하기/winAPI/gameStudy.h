#pragma once

#include "gameNode.h"
#include <cmath>
#include <vector>

#define MAP_WIDTH_MAX 550
#define MAP_HEIGHT_MAX 475
#define CELL_COUNT 10
#define CELL_WIDTH		MAP_WIDTH_MAX / CELL_COUNT	// 가로 10칸
#define CELL_HEIGHT		MAP_HEIGHT_MAX / CELL_COUNT	// 세로 10칸



class gameStudy : public gameNode
{
public:

private:
	image* _pBackgoundImage1;	//백그라운드 이미지
	image* _pBackgoundImage2;	//백그라운드 이미지

	image* _pPlayerImage;
	image* _pEnemyImages;
	
	float* fArrEnemyY;

	image* _endImage;	//끝나는 이미지


	//캐릭터 프레임을 돌리기 위한 변수
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
