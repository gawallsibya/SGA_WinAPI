#pragma once

#include "image.h"

class gameNode
{
private:
	image* _backBuffer;	//¹é¹öÆÛ...
	void setBackBuffer(void);

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	image* getBackBuffer(void) {return _backBuffer;}

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wparam, LPARAM lparam);

	gameNode(void);
	virtual ~gameNode(void);
};
