#include "stdafx.h"
#include "gameOverScene.h"

gameOverScene::gameOverScene()
{
}


gameOverScene::~gameOverScene()
{
}


HRESULT gameOverScene::init(void)
{
	_img = IMAGEMANAGER->findImage("gameOver");

	return S_OK;
}
void gameOverScene::release(void)
{

}

void gameOverScene::update(void)
{
	
}

void gameOverScene::render(void)
{
	_img->render(getMemDC());
}
