#include "stdafx.h"
#include "gameScene.h"


gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init(void)
{
	_stage = new stage;
	_stage->init();

	return S_OK;
}
void gameScene::release(void)
{
	
}

void gameScene::update(void)
{
	_stage->update();
}

void gameScene::render(void)
{
	_stage->render(getMemDC());
}
