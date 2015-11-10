#pragma once

#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarTop; //hp바 탑 이미지
	image* _progressBarBottom; //hp바 백(뒷배경) 이미지

public:
	HRESULT init(int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	//체력바 게이지
	void guage(float currentGuage, float maxGuage);
	//셋터
	void setX(int x) { _x = x;}
	void setY(int y) { _y = y;}
	

	progressBar(void);
	~progressBar(void);
};

