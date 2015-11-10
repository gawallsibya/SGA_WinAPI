#pragma once

#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarTop; //hp�� ž �̹���
	image* _progressBarBottom; //hp�� ��(�޹��) �̹���

public:
	HRESULT init(int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	//ü�¹� ������
	void guage(float currentGuage, float maxGuage);
	//����
	void setX(int x) { _x = x;}
	void setY(int y) { _y = y;}
	

	progressBar(void);
	~progressBar(void);
};

