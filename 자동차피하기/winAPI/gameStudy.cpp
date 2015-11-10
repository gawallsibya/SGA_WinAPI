#include "StdAfx.h"
#include "gameStudy.h"


gameStudy::gameStudy(void)
{
}

gameStudy::~gameStudy(void)
{
}

//�ʱ�ȭ�� ���⼭~
HRESULT gameStudy::init(void)
{
	gameNode::init();

	//��׶��� �̹���
	_pBackgoundImage1 = new image;
	_pBackgoundImage1->init(L"ImageResource/background.bmp", 500, 600);
	_pBackgoundImage1->setX(0);
	_pBackgoundImage1->setY(0);

	_pBackgoundImage2 = new image;
	_pBackgoundImage2->init(L"ImageResource/background.bmp", 500, 600);
	_pBackgoundImage2->setX(_pBackgoundImage1->getX());
	_pBackgoundImage2->setY(_pBackgoundImage1->getY() + _pBackgoundImage1->getHeight());

	_endImage = new image;
	_endImage->init(L"ImageResource/end.bmp", 500, 600);

	_pPlayerImage = new image;
	_pPlayerImage->init(L"ImageResource/car.bmp", 50, 100);
	_pPlayerImage->setX((WINSIZEX / 2) - 50);
	_pPlayerImage->setY(450);

	fArrEnemyY = new float[5]{ -100.f, -300.f, -600.f, -900.f, -1200.f };
	
	_pEnemyImages = new image[5];
	_pEnemyImages[0].init(L"ImageResource/enemy.bmp", 50, 100);
	_pEnemyImages[0].setX(0);
	_pEnemyImages[0].setY(350);

	_pEnemyImages[1].init(L"ImageResource/enemy.bmp", 50, 100);
	_pEnemyImages[1].setX(100);
	_pEnemyImages[1].setY(300);

	_pEnemyImages[2].init(L"ImageResource/enemy.bmp", 50, 100);
	_pEnemyImages[2].setX(200);
	_pEnemyImages[2].setY(250);

	_pEnemyImages[3].init(L"ImageResource/enemy.bmp", 50, 100);
	_pEnemyImages[3].setX(300);
	_pEnemyImages[3].setY(200);

	_pEnemyImages[4].init(L"ImageResource/enemy.bmp", 50, 100);
	_pEnemyImages[4].setX(400);
	_pEnemyImages[4].setY(150);


	_count = 0;
	_frameX = 0;

	_nPlayerMoveSpeed = 2;
	_fSpeed = 0.f;
	_fSpeedMax = 20.f;

	_fEnemySpeed = 15.f;

	_bGameOver = false;

	return S_OK;
}

//�����Ҵ� �Ѱ��� ���⼭ ����� ������ (�̹����� �� ���������~~)
void gameStudy::release(void)
{
	gameNode::release();

	//�̹��� �޸𸮿��� ����
	SAFE_DELETE(_pBackgoundImage1);
	SAFE_DELETE(_pBackgoundImage2);

	SAFE_DELETE(_pPlayerImage);
	SAFE_DELETE_ARRAY(_pEnemyImages);
}

//�������� �ϴ� �ڵ��...
void gameStudy::update(void)
{
	gameNode::update();
	
	// ���� �޸��µ� �ʹ� �ָ����ų� ȭ�� ������ �������� ��ġ �ʱ�ȭ
	for (int i = 0; i < 5; i++)
	{
		_pEnemyImages[i].setY(_pEnemyImages[i].getY() - _fEnemySpeed + _fSpeed);

		if (_pEnemyImages[i].getY() < -WINSIZEY*2 || _pEnemyImages[i].getY() > WINSIZEY*2)
		{
			_pEnemyImages[i].setY(fArrEnemyY[RND->getInt(4)]);
		}
	}

	// key ���� ������Ʈ
	if (KEYMANAGER->isStayKeyDown(VK_UP))	
	{
		_fSpeed += 0.1f;
		if (_fSpeed > _fSpeedMax)
		{
			_fSpeed = _fSpeedMax;
		}
		
	}
	// �յ� �ڵ� ������ ������ ���ݾ� ����
	if (!KEYMANAGER->isStayKeyDown(VK_UP) && !KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_fSpeed -= 0.02f;		
		if (_fSpeed < 0.f)
		{
			_fSpeed = 0.f;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_fSpeed -= 0.1f;
		if (_fSpeed < 0.f)
		{
			_fSpeed = 0.f;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_pPlayerImage->setX(_pPlayerImage->getX() - _nPlayerMoveSpeed);
		
		// �� �浹ó��
		if (isCollisionMap(_pPlayerImage->boundingBox()))
		{
			_pPlayerImage->setX(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_pPlayerImage->setX(_pPlayerImage->getX() + _nPlayerMoveSpeed);

		// �� �浹ó��
		if (isCollisionMap(_pPlayerImage->boundingBox()))
		{
			_pPlayerImage->setX(WINSIZEX - _pPlayerImage->getWidth());
		}
	}

	// player ������Ʈ
	// ������ �浹ó��
	for (int i = 0; i < 5; i++)
	{
		if (isCollisionRect(_pEnemyImages[i].boundingBox(), _pPlayerImage->boundingBox()))
		{
			_bGameOver = true;
		}
		
	}

	// background ������Ʈ
	if (_pBackgoundImage2->getY() >= 0)
	{
		_pBackgoundImage1->setX(0);
		_pBackgoundImage1->setY(0);
	}

	_pBackgoundImage1->setX(_pBackgoundImage1->getX());
	_pBackgoundImage1->setY(_pBackgoundImage1->getY() + _fSpeed);

	_pBackgoundImage2->setX(_pBackgoundImage1->getX());
	_pBackgoundImage2->setY(_pBackgoundImage1->getY() - _pBackgoundImage1->getHeight());


}

void gameStudy::render(HDC hdc)
{
	//����ۿ��� �ѷ��ش� (�̰� ������ �׳� ���Ѱ�)
	HDC backDC = this->getBackBuffer()->getMemDC();

	//���̹��� (�̰͵� ������ �׳� ���Ѱ�)
	//_mapImage->render(backDC, 0, 0); //����ۿ� �׸��� �׸��� ������ġ 0, 0���� ���� �׷���

	//��׶��� �̹���
	_pBackgoundImage1->render(backDC); //��׶��� �̹������� �׸��� ������ġ�� 0, 0��
	_pBackgoundImage2->render(backDC);

	_pPlayerImage->render(backDC);

	for (int i = 0; i < 5; i++)
	{
		_pEnemyImages[i].render(backDC);
	}

	if (_bGameOver)
	{
		_endImage->render(backDC);
	}


	//����� ������ hdc�� �׸��� (�̰͵� ������ �׳� ���Ѱ�)
	this->getBackBuffer()->render(hdc, 0, 0); //��� �̰͵� ������������?
}

bool gameStudy::isCollisionMap(RECT rt)
{
	// x�� �˻�
	if (rt.left < 0 || rt.right > WINSIZEX)
	{
		return true;
	}
	if (rt.top < 0 || rt.bottom > WINSIZEY)
	{
		return true;
	}
	
	// �浹 �������� false
	return false;
}

bool gameStudy::isCollisionRect(RECT rt1, RECT rt2)
{
	int halfX1 = (rt1.right - rt1.left) / 2;
	int halfX2 = (rt2.right - rt2.left) / 2;
	int halfY1 = (rt1.bottom - rt1.top) / 2;
	int halfY2 = (rt2.bottom - rt2.top) / 2;

	int a = abs(rt1.left - rt2.left);
	int b = halfX1 + halfX2;
	if (a < b)
	{
		a = abs(rt1.top - rt2.top);
		int b = halfY1 + halfY2;
		if (a < b)
		{
			return TRUE;
		}
	}
	return FALSE;
}