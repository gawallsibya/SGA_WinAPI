//======================================================
// 2014.10.22 ## 헤더파일 써준다 ##
//======================================================
#include "stdafx.h"
#include "gameStudy.h"

//======================================================
// 2014.10.22 ## 전역변수 써준다 ##
//======================================================
HINSTANCE _hInstance; 
HWND _hWnd;
POINT _ptMouse = {0, 0};

//게임스터디 클래스
gameStudy _gs;

//======================================================
// 2014.10.22 ## 함수의 프로토타입 써준다 ##
//======================================================

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					 LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	//MSG : 운영체제에서 발행하는 메시지 정보를 저장하기 위한 구조체
	MSG message;		

	//WNDCLASS : 윈도우의 정보를 저장하기 위한 구조체
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;		//클래스 여분 메모리
	wndClass.cbWndExtra = 0;		//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//아이콘
	wndClass.hInstance = hInstance;									//인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져
	wndClass.lpszClassName = WINNAME;								//클래스이름
	wndClass.lpszMenuName = NULL;									//메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 스타일

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

	//윈도우 생성
	_hWnd = CreateWindow(
		WINNAME,				//윈도우 클래스의 이름
		WINNAME,				//윈도우 타이틀바 이름
		WINSTYLE,				//윈도우 스타일
		WINSTARTX,				//윈도우 화면좌표 x
		WINSTARTY,				//윈도우 화면좌표 y
		WINSIZEX,				//윈도우 화면좌표 width
		WINSIZEY,				//윈도우 화면좌표 height
		NULL,					//부모 윈도우
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스 지정
		NULL);					//윈도우 및 자식 윈도우를 생성하면
								//지정해주되 그렇지 않으면 NULL

	//화면 작업 사이즈 영역 계산
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//화면에 윈도우 보여준다
	ShowWindow(_hWnd, nCmdShow);


	if (FAILED(_gs.init()))
	{
		//실패하면 바로 종료.
		return 0;
	}

	while (true) //게임용
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0F);
			_gs.update(); //스터디 업데이트
			_gs.render(); //스터디 렌더
		}
	}

	//스터디 해제..
	_gs.release();
	
	/*
	//일반 프로그램용
	while (GetMessage(&message, 0, 0, 0)) 
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	*/


	//윈도우 클래스 등록 해제...
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}
//======================================================
//======================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, 
						 WPARAM wParam, LPARAM lParam)
{
	return _gs.MainProc(hWnd, iMessage, wParam, lParam);
}
//======================================================
//======================================================
void setWindowSize(int x, int y, int width, int height)
{
	//윈도우 작업영역 지정
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);
	//위의 RECT 정보로 윈도우 사이즈 세팅
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}

