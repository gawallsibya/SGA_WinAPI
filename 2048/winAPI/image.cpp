#include "stdafx.h"
#include "image.h"

#pragma comment (lib, "msimg32.lib")

//��� �̴ϼ� ������� �ʱ�ȭ
image::image(void) :_imageInfo(NULL), _fileName(NULL), _trans(false), _transColor(RGB(0, 0, 0))
{
}

image::~image(void)
{
}

//�� ��Ʈ�� �̹��� �����
HRESULT	image::init(int width, int height)
{
	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC 
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ش�

	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����

	//�̹��� ���� ����
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

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���� �÷� ����
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


//���ҽ��κ��� �о�´�
HRESULT	image::init(const DWORD resID, int width, 
	int height, BOOL trans, COLORREF transColor)
{
	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
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

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���� �÷� ����
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�̹��� ���� (���Ϸκ��� �о�´�)
HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����...
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImageA(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
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

	//���� ��� �̸� ����~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


HRESULT image::init(const char* fileName, int width, int height, 
BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����...
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImageA(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
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

	//���� ��� �̸� ����~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�̹��� + ������ ���� �ʱ�ȭ
HRESULT image::init(const char* fileName, float x, float y,
	int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����...
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImageA(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
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

	//���� ��� �̸� ����~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


HRESULT image::init(const char* fileName, int width, int height, 
					int frameX, int frameY, BOOL trans, 
					COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����...
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImageA(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
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

	//���� ��� �̸� ����~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//����
void image::release(void)
{
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//���� �÷� �ʱ�ȭ
		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}


//���� Ű ����
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

//����
void image::render(HDC hdc)
{
	if (_trans)
	{
		//TransparentBlt�� �ִ�
		//
		GdiTransparentBlt(hdc,	//������ ����� DC
			(int)_imageInfo->x,	//����� ��ǥ ������ X
			(int)_imageInfo->y,	//����� ��ǥ ������ Y
			_imageInfo->width,	//����� ũ�� width
			_imageInfo->height,	//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC,
			0, 0,				//���� ��������
			_imageInfo->width,	//����� �������� width
			_imageInfo->height,	//����� �������� height
			_transColor);		//���翡�� ������ ���� ����
	}
	else 
	{
		//BitBlt �� DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ��̴�.
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			_imageInfo->width, _imageInfo->height, 
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		//TransparentBlt�� �ִ�
		//
		GdiTransparentBlt(hdc,	//������ ����� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			_imageInfo->width,	//����� ũ�� width
			_imageInfo->height,	//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC,
			0, 0,				//���� ��������
			_imageInfo->width,	//����� �������� width
			_imageInfo->height,	//����� �������� height
			_transColor);		//���翡�� ������ ���� ����
	}
	else 
	{
		//BitBlt �� DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ��̴�.
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
		//TransparentBlt�� �ִ�
		//
		GdiTransparentBlt(hdc,	//������ ����� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			sourWidth,			//����� ũ�� width
			sourHeight,			//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC,
			sourX,				//���� �������� x
			sourY,				//���� �������� y
			sourWidth,			//����� �������� width
			sourHeight,			//����� �������� height
			_transColor);		//���翡�� ������ ���� ����
	}
	else 
	{
		//BitBlt �� DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ��̴�.
		BitBlt(hdc, destX, destY, 
			sourWidth, sourHeight, 
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::render(HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		//TransparentBlt�� �ִ�
		//
		GdiTransparentBlt(hdc,	//������ ����� DC
			(int)_imageInfo->x,	//����� ��ǥ ������ X
			(int)_imageInfo->y,	//����� ��ǥ ������ Y
			sourWidth,			//����� ũ�� width
			sourHeight,			//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC,
			sourX,				//���� �������� x
			sourY,				//���� �������� y
			sourWidth,			//����� �������� width
			sourHeight,			//����� �������� height
			_transColor);		//���翡�� ������ ���� ����
	}
	else 
	{
		//BitBlt �� DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ��̴�.
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			sourWidth, sourHeight, 
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}
//��������
void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//�ɼ� ���� ������ ��� ����
	if(offsetX < 0 ) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if(offsetY < 0 ) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� �ҽ��� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ����
	RECT rcDest;

	//�׷����� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ����
	for(int y = 0 ; y < drawAreaH ; y += sourHeight)
	{
		//�ҽ� ���� ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ��� ������ �׸��� ȭ���� �Ѿ�ٸ�
		if(y + sourHeight > drawAreaH)
		{
			//�Ѿ �縸ŭ ���� ���� �ø���.
			rcSour.bottom -=  (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}	

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ����
		for(int x = 0 ; x < drawAreaW ; x += sourWidth)
		{
			//�ҽ��� ���� ���� ���
			rcSour.left	= (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ��� ������ �׸��� ȭ���� �Ѿ�ٸ�
			if(x + sourWidth > drawAreaW)
			{
				//�Ѿ �� ��ŭ ����Ʈ ���� ��������..
				rcSour.right -=  (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			
			//�׷����� ����
			rcDest.left	= x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;


			//�׸���.
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top );
			
		}
	}
}

//������ ����
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

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}
