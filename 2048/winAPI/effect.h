#pragma once

#include "gameNode.h"

class image;
class animation;

class effect : public gameNode
{
protected:
	int _x;	//effect ��ǥ x;
	int _y;	//effect ��ǥ y;

	image* _effectImage;			//�̹���
	animation* _effectAnimation;	//�ִϸ��̼�
	bool _isRunning;				//�����ֳ�?
	float _elapsedTime;				//����ð�

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

