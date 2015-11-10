#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode(void)
{
}

gameNode::~gameNode(void)
{
}

HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if(managerInit)
	{
		KEYMANAGER->init();				//키매니져 셋팅
		IMAGEMANAGER->init();			//이미지매니져 셋팅	
		TIMEMANAGER->init();			//타임매니져 세팅
		TXTDATA->init();				//텍스트데이터 셋팅
		EFFECTMANAGER->init();			//이펙트 매니져 셋팅
		SCENEMANAGER->init();			//씬매니져 셋팅
	}

	return S_OK;
}

void gameNode::release(void)
{
	if(_managerInit)
	{
		//키매니져 싱글톤 해제
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//이미지 매니져 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//타임매니져 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		//TXTDATA 싱글톤 해제
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		//effectManager 싱글톤 해제
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		//씬매니져 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
	}

	//DC해제
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update(void)
{
}

void gameNode::render(void)
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
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

