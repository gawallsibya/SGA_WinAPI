// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
//#include "Resource.h"

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//���� ���� ������ϵ�~~
#include "commonMacroFunction.h"
#include "commonVirtualKey.h"
#include "randomFunction.h"
#include "keyManager.h"

//======================================================
// 2014.10.22 ## �����ι� ���ش� ## 
//======================================================
#define WINNAME (LPTSTR)(TEXT("WindowAPI"))
#define WINSTARTX 300
#define WINSTARTY 100
#define WINSIZEX 550
#define WINSIZEY 550
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)		{ if(p) { delete[] (p);		(p)=NULL; } }
#define SAFE_RELEASE(p)			{ if(p) { (p)->release();	(p)=NULL; } }

//�̱���
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()

//======================================================
// 2014.10.22 ## �������� ���ش� ##
//======================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
