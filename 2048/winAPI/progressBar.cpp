#include "stdafx.h"
#include "progressBar.h"

progressBar::progressBar(void)
{
}

progressBar::~progressBar(void)
{
}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->addImage("barTop", "hpBarTop.bmp", static_cast<float>(x), static_cast<float>(y), width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage("barBottom", "hpBarBottom.bmp", static_cast<float>(x), static_cast<float>(y), width, height, true, RGB(255, 0, 255));

	_width = static_cast<float>(_progressBarTop->getWidth());

	return S_OK;
}

void progressBar::release(void)
{
}

void progressBar::update(void)
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarBottom->getWidth(), _progressBarBottom->getHeight());
}

void progressBar::render(void)
{
	IMAGEMANAGER->render("barBottom", getMemDC(), 
		static_cast<int>(_rcProgress.left + _progressBarBottom->getWidth() / 2),
		static_cast<int>(_y + _progressBarBottom->getHeight() / 2),
		0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	IMAGEMANAGER->render("barTop", getMemDC(), 
		_rcProgress.left + _progressBarTop->getWidth() / 2,
		_y + _progressBarTop->getHeight() / 2,
		0, 0,
		static_cast<int>(_width), _progressBarTop->getHeight());
}

//체력바 게이지
void progressBar::guage(float currentGuage, float maxGuage)
{
	_width = (currentGuage / maxGuage) * _progressBarBottom->getWidth();
}