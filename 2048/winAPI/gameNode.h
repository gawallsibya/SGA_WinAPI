#pragma once

#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backbuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	image* getBackBuffer(void) {return _backBuffer;}
	HDC getMemDC() {return _backBuffer->getMemDC();} //메모리버퍼
	HDC getHDC() {return _hdc;} //화면버퍼

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wparam, LPARAM lparam);

	gameNode(void);
	virtual ~gameNode(void);
};
