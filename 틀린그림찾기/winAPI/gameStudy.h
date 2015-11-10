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
	//image* _mapImage;	//��� ��� �̹���
	image* _bgImage;	//��׶��� �̹���
	image* _endImage;	//������ �̹���

	vector<image*> _vBingos;
	list<image*> _lMisses;

	BINGO_BOX* _bingoBox1;
	BINGO_BOX* _bingoBox2;

	//ĳ���� �������� ������ ���� ����
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
