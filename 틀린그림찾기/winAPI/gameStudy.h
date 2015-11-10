#pragma once

#include "gameNode.h"
#include <cmath>
#include <vector>
#include <list>

#define BINGOMAX 7

class gameStudy : public gameNode
{
public:
	typedef struct bingoBox
	{
		RECT bingoBundingBox;
		BOOL isCheck;
		void init(int left, int top, int right, int bottom)
		{
			bingoBundingBox = { left, top, right, bottom };
			isCheck = false;
		}
		const POINTFLOAT GetCenter() const
		{
			POINTFLOAT fPt;
			fPt.x = static_cast<float>((bingoBundingBox.right - bingoBundingBox.left) / 2 + bingoBundingBox.left);
			fPt.y = static_cast<float>((bingoBundingBox.bottom - bingoBundingBox.top) / 2 + bingoBundingBox.top);
			return fPt;
		}
	}BINGO_BOX;

private:
	//image* _mapImage;	//흰색 빈맵 이미지
	image* _bgImage;	//백그라운드 이미지
	image* _endImage;	//끝나는 이미지

	vector<image*> _vBingos;
	list<image*> _lMisses;

	BINGO_BOX* _bingoBox1;
	BINGO_BOX* _bingoBox2;

	//캐릭터 프레임을 돌리기 위한 변수
	int _count;
	int _frameX;
	int _secound;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	gameStudy(void);
	~gameStudy(void);
};
