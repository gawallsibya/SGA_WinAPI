#pragma once

#include "gameNode.h"
#include <cmath>
#include "stone.h"
#include <vector>

#define MAPSIZE_MAX 19

enum PLAYER{ P1, P2 };
enum WIN { NONE, WIN_BLACK, WIN_WHITE };

class gameStudy : public gameNode
{
public:
	struct mapRect
	{
		int left;
		int top;
		int right;
		int bottom;

		STONECOLOR stoneColor;

		mapRect()
		{
			left = 0;
			top = 0;
			right = 0;
			bottom = 0;

			stoneColor = STONECOLOR::STONE_NONE;
		}

		void setCenter(int x, int y)
		{
			int halfSize = 27 / 2;

			left = x - halfSize;
			top = y - halfSize;
			right = x + halfSize;
			bottom = y + halfSize;
		}
	};


private:
	//image* _mapImage;	//흰색 빈맵 이미지
	image* _pMapImage;	//백그라운드 이미지
	image* _endImage;	//끝나는 이미지

	mapRect** _ppMapRects;
	
	vector<stone*> _vBlackStones;
	vector<stone*> _vWhiteStones;

	//캐릭터 프레임을 돌리기 위한 변수
	int _count;
	int _frameX;
	int _secound;
	WIN _winner;

	PLAYER _turn;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	bool collisionMap();
	void dropStone(vector<stone*>& vStone, int x, int y, STONECOLOR color);
	POINT mousePointToMapPoint();
	bool searchLine(int x, int y);

	gameStudy(void);
	~gameStudy(void);
};
