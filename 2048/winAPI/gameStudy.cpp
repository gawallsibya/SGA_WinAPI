#include "stdafx.h"
#include "gameStudy.h"
#include "gameScene.h"
#include "gameOverScene.h"

gameStudy::gameStudy(void)
{
}

gameStudy::~gameStudy(void)
{
}

//초기화는 여기서~
HRESULT gameStudy::init(void)
{
	gameNode::init(true);

	// 이미지 로드
	IMAGEMANAGER->addImage("mapImage", "ImageResource/map.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("block", "ImageResource/block.bmp", 1100, 100, 11, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameOver", "ImageResource/gameOver.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));

	gameNode* _gameScene = new gameScene;
	gameNode* _gameOVerScene = new gameOverScene;

	SCENEMANAGER->addScene("gameScene", _gameScene);
	SCENEMANAGER->addScene("gameOverScene", _gameOVerScene);

	SCENEMANAGER->changeScene("gameScene");

	return S_OK;
}

void gameStudy::release(void)
{
	gameNode::release();
}

//움직여야 하는 코드들...
void gameStudy::update(void)
{
	SCENEMANAGER->update();
}

void gameStudy::render(void)
{
	//맵이미지
	IMAGEMANAGER->findImage("mapImage")->render(getMemDC(), 0, 0);

	SCENEMANAGER->render();

	//타임매니져 렌더
	TIMEMANAGER->render(getMemDC());
	
	//백버퍼 내용을 hdc에 그린다 (렌더에 그냥 놔둘것)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

