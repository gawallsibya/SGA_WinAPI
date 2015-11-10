#pragma once

#include "gameNode.h"

class image;
class animation;

class effect : public gameNode
{
protected:
	int _x;	//effect 좌표 x;
	int _y;	//effect 좌표 y;

	image* _effectImage;			//이미지
	animation* _effectAnimation;	//애니메이션
	bool _isRunning;				//돌고있냐?
	float _elapsedTime;				//경과시간

public:
	HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void startEffect(int x, int y);
	void killEffect(void);

	BOOL getIsRunning(void) {return _isRunning;}

	effect(void);
	virtual ~effect(void);

};

