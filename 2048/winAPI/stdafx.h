// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once
//======================================================
// 2014.10.22 ## 헤더파일 써준다 ##
//======================================================

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN	//MFC가 아닌 응용 프로그램의 경우에는 
							//WIN32_LEAN_AND_MEAN를 선언해 commdlg.h등등
							//필요없는 헤더파일을 인클루드 하지 않게 해준다.
		
#include <windows.h>		//윈도우 헤더파일 인클루드
#include <stdlib.h>			//스탠다드 라이브러리 인클루드~ (srand)
#include <stdio.h>			//스탠다드 입출력 헤더 인클루드~ (printf, scanf 등등..)
#include <tchar.h>			//윈도우에서 사용할 문자열 출력 헤더 인클루드~
							//MBCS (Multi Byte Character Set) 
							//-> 기존에 사용한던 멀티바이트 형태의 문자열~
							//WBCS (Wide Byte Character Set)
							//-> 모든 문자를 2바이트로 처리~~, 유니코드 기반...

//내가 만든 헤더파일들~~
#include "commonMacroFunction.h"
#include "commonVirtualKey.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "txtData.h"
#include "utils.h"
#include "effectManager.h"
#include "sceneManager.h"

//======================================================
// 2014.10.22 ## 디파인문 써준다 ## 
//======================================================
#define WINNAME (LPTSTR)(TEXT("WindowAPI"))
#define WINSTARTX 300
#define WINSTARTY 000
#define WINSIZEX 500
#define WINSIZEY 500
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)		{ if(p) { delete[] (p);		(p)=NULL; } }
#define SAFE_RELEASE(p)			{ if(p) { (p)->release();	(p)=NULL; } }

//내가 만든 네임스페이스 사용하기
using namespace MY_UTIL;

//싱글톤
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()

//======================================================
// 2014.10.22 ## 전역변수 써준다 ##
//======================================================
extern HINSTANCE _hInstance; 
extern HWND _hWnd;
extern POINT _ptMouse;
						

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
