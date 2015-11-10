#pragma once

#include "gameNode.h"
#include <cmath>
#include "monster.h"

#define MONTER_MAX 9
class gameStudy : public gameNode
{
private:
	//image* _mapImage;	//��� ��� �̹���
	image* _bgImage;	//��׶��� �̹���
	image* _endImage;	//������ �̹���

	monster* _monster;


	//ĳ���� �������� ������ ���� ����
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
