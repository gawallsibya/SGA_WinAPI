#include "StdAfx.h"
#include "gameStudy.h"


gameStudy::gameStudy(void)
{
}

gameStudy::~gameStudy(void)
{
}

//초기화는 여기서~
HRESULT gameStudy::init(void)
{
	gameNode::init();

	//백그라운드 이미지
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

//동적할당 한것은 여기서 지우고 나가셈 (이미지들 다 삭제해줘랑~~)
void gameStudy::release(void)
{
	gameNode::release();

	//이미지 메모리에서 해제
	SAFE_DELETE(_pBackgoundImage1);
	SAFE_DELETE(_pBackgoundImage2);

	SAFE_DELETE(_pPlayerImage);
	SAFE_DELETE_ARRAY(_pEnemyImages);
}

//움직여야 하는 코드들...
void gameStudy::update(void)
{
	gameNode::update();
	
	// 적이 달리는데 너무 멀리가거나 화면 밑으로 뒤쳐지면 위치 초기화
	for (int i = 0; i < 5; i++)
	{
		_pEnemyImages[i].setY(_pEnemyImages[i].getY() - _fEnemySpeed + _fSpeed);

		if (_pEnemyImages[i].getY() < -WINSIZEY*2 || _pEnemyImages[i].getY() > WINSIZEY*2)
		{
			_pEnemyImages[i].setY(fArrEnemyY[RND->getInt(4)]);
		}
	}

	// key 관련 업데이트
	if (KEYMANAGER->isStayKeyDown(VK_UP))	
	{
		_fSpeed += 0.1f;
		if (_fSpeed > _fSpeedMax)
		{
			_fSpeed = _fSpeedMax;
		}
		
	}
	// 앞도 뒤도 누르지 않으면 조금씩 감속
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
		
		// 맵 충돌처리
		if (isCollisionMap(_pPlayerImage->boundingBox()))
		{
			_pPlayerImage->setX(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_pPlayerImage->setX(_pPlayerImage->getX() + _nPlayerMoveSpeed);

		// 맵 충돌처리
		if (isCollisionMap(_pPlayerImage->boundingBox()))
		{
			_pPlayerImage->setX(WINSIZEX - _pPlayerImage->getWidth());
		}
	}

	// player 업데이트
	// 적과의 충돌처리
	for (int i = 0; i < 5; i++)
	{
		if (isCollisionRect(_pEnemyImages[i].boundingBox(), _pPlayerImage->boundingBox()))
		{
			_bGameOver = true;
		}
		
	}

	// background 업데이트
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
	//백버퍼에서 뿌려준다 (이건 렌더에 그냥 놔둘것)
	HDC backDC = this->getBackBuffer()->getMemDC();

	//맵이미지 (이것두 렌더에 그냥 놔둘것)
	//_mapImage->render(backDC, 0, 0); //백버퍼에 그림을 그리는 시작위치 0, 0에서 부터 그려라

	//백그라운드 이미지
	_pBackgoundImage1->render(backDC); //백그라운드 이미지또한 그리는 시작위치는 0, 0임
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


	//백버퍼 내용을 hdc에 그린다 (이것두 렌더에 그냥 놔둘것)
	this->getBackBuffer()->render(hdc, 0, 0); //당근 이것도 마찬가지겠지?
}

bool gameStudy::isCollisionMap(RECT rt)
{
	// x축 검사
	if (rt.left < 0 || rt.right > WINSIZEX)
	{
		return true;
	}
	if (rt.top < 0 || rt.bottom > WINSIZEY)
	{
		return true;
	}
	
	// 충돌 안했으면 false
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