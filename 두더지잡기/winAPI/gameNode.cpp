#include "StdAfx.h"
#include "gameNode.h"

gameNode::gameNode(void)
{
}

gameNode::~gameNode(void)
{
}

HRESULT gameNode::init(void)
{
	SetTimer(_hWnd, 1, 10, NULL);	//타이머 셋팅
	KEYMANAGER->init();				//키매니져 셋팅
	setBackBuffer();				//백버퍼 셋팅

	return S_OK;
}

void gameNode::release(void)
{
	//백버퍼 해제
	if (_backBuffer) delete _backBuffer;

	//타이머 해제
	KillTimer(_hWnd, 1);

	//키매니져 싱글톤 해제
	KEYMANAGER->releaseSingleton();
}

void gameNode::update(void)
{
	//화면갱신
	InvalidateRect(_hWnd, NULL, false);
}

//백버퍼 세팅하기
void gameNode::setBackBuffer(void)
{
	_backBuffer = new image;
	_backBuffer->init(WINSIZEX, WINSIZEY);
}

void gameNode::render(HDC hdc)
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
		case WM_TIMER:
			this->update();
		break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			this->render(hdc);
			EndPaint(hWnd, &ps);
		break;
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<int>(LOWORD(lParam));
			_ptMouse.y = static_cast<int>(HIWORD(lParam));
		break;
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

