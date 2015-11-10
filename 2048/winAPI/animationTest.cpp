#include "StdAfx.h"
#include "animationTest.h"

animationTest::animationTest(void)
{
}

animationTest::~animationTest(void)
{
}

HRESULT animationTest::init(void)
{
	gameNode::init();

	IMAGEMANAGER->addImage("explosion0", 
		"explosion0.bmp", 320, 320, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("explosion1", 
		"explosion0.bmp", 320, 320, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("explosion2", 
		"explosion0.bmp", 320, 320, true, RGB(255, 0, 255));

	_ani1 = new animation;
	_ani1->init(320, 320, 64, 64);
	_ani1->setDefPlayFrame(true, true);
	_ani1->setFPS(1);

	int arrIdx[12] = {23, 10, 2, 6, 19, 1, 2, 3, 9, 10, 11, 21};
	_ani2 = new animation;
	_ani2->init(320, 320, 64, 64);
	_ani2->setPlayFrame(arrIdx, 12, true);
	_ani2->setFPS(1);

	_ani3 = new animation;
	_ani3->init(320, 320, 64, 64);
	_ani3->setPlayFrame(0, 3, true, true);
	_ani3->setFPS(1);

	return S_OK;
}

void animationTest::release(void)
{
	gameNode::release();
}

void animationTest::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		_ani1->start();
	}

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_ani2->start();
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		_ani3->start();
	}

	_ani1->frameUpdate(1.0f);
	_ani2->frameUpdate(1.0f);
	_ani3->frameUpdate(1.0f);
}

void animationTest::render(void)
{
	IMAGEMANAGER->findImage("explosion0")->aniRender(getMemDC(),
		100, 100, _ani1);

	IMAGEMANAGER->findImage("explosion1")->aniRender(getMemDC(),
		100, 200, _ani2);

	IMAGEMANAGER->findImage("explosion2")->aniRender(getMemDC(),
		100, 300, _ani3);
}
