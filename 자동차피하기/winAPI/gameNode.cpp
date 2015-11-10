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
	SetTimer(_hWnd, 1, 10, NULL);	//Ÿ�̸� ����
	KEYMANAGER->init();				//Ű�Ŵ��� ����
	setBackBuffer();				//����� ����

	return S_OK;
}

void gameNode::release(void)
{
	//����� ����
	if (_backBuffer) delete _backBuffer;

	//Ÿ�̸� ����
	KillTimer(_hWnd, 1);

	//Ű�Ŵ��� �̱��� ����
	KEYMANAGER->releaseSingleton();
}

void gameNode::update(void)
{
	//ȭ�鰻��
	InvalidateRect(_hWnd, NULL, false);
}

//����� �����ϱ�
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

