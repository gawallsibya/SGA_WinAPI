// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
//#include "Resource.h"

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//내가 만든 헤더파일들~~
#include "commonMacroFunction.h"
#include "commonVirtualKey.h"
#include "randomFunction.h"
#include "keyManager.h"

//======================================================
// 2014.10.22 ## 디파인문 써준다 ## 
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

//싱글톤
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()

//======================================================
// 2014.10.22 ## 전역변수 써준다 ##
//======================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
