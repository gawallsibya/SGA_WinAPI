#include "StdAfx.h"
#include "image.h"

#pragma comment (lib, "msimg32.lib")

//멤버 이니셜 라이즈로 초기화
image::image(void) :_imageInfo(NULL), _fileName(NULL), _trans(false), _transColor(RGB(0, 0, 0))
{
}

image::~image(void)
{
}

//빈 비트맵 이미지 만든다
HRESULT	image::init(int width, int height)
{
	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC 
	//비트맵을 출력하기 위해서 메모리 DC를 만들어 준다

	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵 생성

	//이미지 정보 생성
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_EMPTY;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x				= 0;
	_imageInfo->y				= 0;
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width;
	_imageInfo->frameHeight		= height;
	_imageInfo->maxFrameX		= 0;
	_imageInfo->maxFrameY		= 0;

	_fileName					= NULL;

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//투명 컬러 셋팅
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


//리소스로부터 읽어온다
HRESULT	image::init(const DWORD resID, int width, 
	int height, BOOL trans, COLORREF transColor)
{
	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_RESOURCE;
	_imageInfo->resID			= resID;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x				= 0;
	_imageInfo->y				= 0;
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width;
	_imageInfo->frameHeight		= height;
	_imageInfo->maxFrameX		= 0;
	_imageInfo->maxFrameY		= 0;

	_fileName				= NULL;

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//투명 컬러 셋팅
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//이미지 설정 (파일로부터 읽어온다)
HRESULT image::init(const WCHAR* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//파일 경로가 잘못 되었으면...
	if (fileName == NULL) return E_FAIL;

	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x				= x - (width / 2);
	_imageInfo->y				= y - (height / 2);
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width;
	_imageInfo->frameHeight		= height;
	_imageInfo->maxFrameX		= 0;
	_imageInfo->maxFrameY		= 0;

	//파일 경로 이름 복사~~
	int len = lstrlen(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpy(_fileName, fileName);
	
	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


HRESULT image::init(const WCHAR* fileName, int width, int height, 
BOOL trans, COLORREF transColor)
{
	//파일 경로가 잘못 되었으면...
	if (fileName == NULL) return E_FAIL;

	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x				= 0;
	_imageInfo->y				= 0;
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width;
	_imageInfo->frameHeight		= height;
	_imageInfo->maxFrameX		= 0;
	_imageInfo->maxFrameY		= 0;

	//파일 경로 이름 복사~~
	int len = lstrlen(fileName) + 1;
	_fileName = new WCHAR[len];
	lstrcpyn(_fileName, fileName, len);

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//이미지 + 프레임 파일 초기화
HRESULT image::init(const WCHAR* fileName, float x, float y,
	int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//파일 경로가 잘못 되었으면...
	if (fileName == NULL) return E_FAIL;

	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x				= x - (width / 2);
	_imageInfo->y				= y - (height / 2);
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width / frameX;
	_imageInfo->frameHeight		= height / frameY;
	_imageInfo->maxFrameX		= frameX - 1;
	_imageInfo->maxFrameY		= frameY - 1;

	//파일 경로 이름 복사~~
	int len = lstrlen(fileName) + 1;
	_fileName = new WCHAR[len];
	lstrcpyn(_fileName, fileName, len);

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


HRESULT image::init(const WCHAR* fileName, int width, int height,
					int frameX, int frameY, BOOL trans, 
					COLORREF transColor)
{
	//파일 경로가 잘못 되었으면...
	if (fileName == NULL) return E_FAIL;

	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x				= 0;
	_imageInfo->y				= 0;
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width / frameX;
	_imageInfo->frameHeight		= height / frameY;
	_imageInfo->maxFrameX		= frameX - 1;
	_imageInfo->maxFrameY		= frameY - 1;

	//파일 경로 이름 복사~~
	int len = lstrlen(fileName) + 1;
	_fileName = new WCHAR[len];
	lstrcpyn(_fileName, fileName, len);

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//삭제
void image::release(void)
{
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//투명 컬러 초기화
		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}


//투명 키 셋팅
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

//렌더
void image::render(HDC hdc)
{
	if (_trans)
	{
		//TransparentBlt도 있다
		//
		GdiTransparentBlt(hdc,	//복사할 장소의 DC
			(int)_imageInfo->x,	//복사될 좌표 시작점 X
			(int)_imageInfo->y,	//복사될 좌표 시작점 Y
			_imageInfo->width,	//복사될 크기 width
			_imageInfo->height,	//복사될 크기 height
			_imageInfo->hMemDC,	//복사대상 DC,
			0, 0,				//복사 시작지점
			_imageInfo->width,	//복사될 영역지정 width
			_imageInfo->height,	//복사될 영역지정 height
			_transColor);		//복사에서 제외할 색상 지정
	}
	else 
	{
		//BitBlt 는 DC간의 영역끼리 서로 고속복사를 해주는 함수이다.
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			_imageInfo->width, _imageInfo->height, 
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		//TransparentBlt도 있다
		//
		GdiTransparentBlt(hdc,	//복사할 장소의 DC
			destX,				//복사될 좌표 시작점 X
			destY,				//복사될 좌표 시작점 Y
			_imageInfo->width,	//복사될 크기 width
			_imageInfo->height,	//복사될 크기 height
			_imageInfo->hMemDC,	//복사대상 DC,
			0, 0,				//복사 시작지점
			_imageInfo->width,	//복사될 영역지정 width
			_imageInfo->height,	//복사될 영역지정 height
			_transColor);		//복사에서 제외할 색상 지정
	}
	else 
	{
		//BitBlt 는 DC간의 영역끼리 서로 고속복사를 해주는 함수이다.
		BitBlt(hdc, destX, destY, 
			_imageInfo->width, _imageInfo->height, 
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, 
		int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		//TransparentBlt도 있다
		//
		GdiTransparentBlt(hdc,	//복사할 장소의 DC
			destX,				//복사될 좌표 시작점 X
			destY,				//복사될 좌표 시작점 Y
			sourWidth,			//복사될 크기 width
			sourHeight,			//복사될 크기 height
			_imageInfo->hMemDC,	//복사대상 DC,
			sourX,				//복사 시작지점 x
			sourY,				//복사 시작지점 y
			sourWidth,			//복사될 영역지정 width
			sourHeight,			//복사될 영역지정 height
			_transColor);		//복사에서 제외할 색상 지정
	}
	else 
	{
		//BitBlt 는 DC간의 영역끼리 서로 고속복사를 해주는 함수이다.
		BitBlt(hdc, destX, destY, 
			sourWidth, sourHeight, 
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::render(HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		//TransparentBlt도 있다
		//
		GdiTransparentBlt(hdc,	//복사할 장소의 DC
			(int)_imageInfo->x,	//복사될 좌표 시작점 X
			(int)_imageInfo->y,	//복사될 좌표 시작점 Y
			sourWidth,			//복사될 크기 width
			sourHeight,			//복사될 크기 height
			_imageInfo->hMemDC,	//복사대상 DC,
			sourX,				//복사 시작지점 x
			sourY,				//복사 시작지점 y
			sourWidth,			//복사될 영역지정 width
			sourHeight,			//복사될 영역지정 height
			_transColor);		//복사에서 제외할 색상 지정
	}
	else 
	{
		//BitBlt 는 DC간의 영역끼리 서로 고속복사를 해주는 함수이다.
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			sourWidth, sourHeight, 
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

//프레임 렌더
void image::frameRender(HDC hdc, int destX, int destY)
{
	if(_trans)
	{
		GdiTransparentBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth, 
			_imageInfo->frameHeight, _transColor);	
	}

	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY,
	int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if (currentFrameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;

	if(_trans)
	{
		GdiTransparentBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth, 
			_imageInfo->frameHeight, _transColor );	
	}

	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}
