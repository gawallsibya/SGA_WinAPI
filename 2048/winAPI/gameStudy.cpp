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

//�ʱ�ȭ�� ���⼭~
HRESULT gameStudy::init(void)
{
	gameNode::init(true);

	// �̹��� �ε�
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

//�������� �ϴ� �ڵ��...
void gameStudy::update(void)
{
	SCENEMANAGER->update();
}

void gameStudy::render(void)
{
	//���̹���
	IMAGEMANAGER->findImage("mapImage")->render(getMemDC(), 0, 0);

	SCENEMANAGER->render();

	//Ÿ�ӸŴ��� ����
	TIMEMANAGER->render(getMemDC());
	
	//����� ������ hdc�� �׸��� (������ �׳� ���Ѱ�)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

