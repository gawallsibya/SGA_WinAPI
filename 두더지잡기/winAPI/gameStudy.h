#pragma once

#include "gameNode.h"
#include <cmath>
#include "monster.h"

#define MONTER_MAX 9
class gameStudy : public gameNode
{
private:
	//image* _mapImage;	//흰색 빈맵 이미지
	image* _bgImage;	//백그라운드 이미지
	image* _endImage;	//끝나는 이미지

	monster* _monster;


	//캐릭터 프레임을 돌리기 위한 변수
	int _count;
	int _frameX;
	int _secound;
	int _killCount;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void initMonsterPoint(void);

	gameStudy(void);
	~gameStudy(void);
};
