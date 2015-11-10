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
	_bgImage = new image;
	_bgImage->init(L"ImageResource/background.bmp", 640, 480);
	
	_endImage = new image;
	_endImage->init(L"ImageResource/end.bmp", 960, 720);

	_monster = new monster[MONTER_MAX];
	_monster[0].changeState(new monsterState(STATE::STATE_NONE));
	_monster[1].changeState(new monsterState(STATE::STATE_NONE));
	_monster[2].changeState(new monsterState(STATE::STATE_NONE));
	_monster[3].changeState(new monsterState(STATE::STATE_NONE));
	_monster[4].changeState(new monsterState(STATE::STATE_NONE));
	_monster[5].changeState(new monsterState(STATE::STATE_NONE));
	_monster[6].changeState(new monsterState(STATE::STATE_NONE));
	_monster[7].changeState(new monsterState(STATE::STATE_NONE));
	_monster[8].changeState(new monsterState(STATE::STATE_NONE));

	//위치 설정
	initMonsterPoint();

	_count = 0;
	_frameX = 0;
	_killCount = 0;

	return S_OK;
}

//동적할당 한것은 여기서 지우고 나가셈 (이미지들 다 삭제해줘랑~~)
void gameStudy::release(void)
{
	gameNode::release();
	
	//이미지 메모리에서 해제
	//SAFE_DELETE(_mapImage);

	SAFE_DELETE(_bgImage);
}

//움직여야 하는 코드들...
void gameStudy::update(void)
{
	gameNode::update();

	//상태값 변화 업데이트
	for (int i = 0; i < MONTER_MAX; i++)
	{
		_monster[i].getMyState()->update();

		if (_monster[i].getMyState()->getIsStop())
		{
			switch (_monster[i].getMyState()->getStateInfo())
			{
			case STATE::STATE_NONE:
				break;

			case STATE::STATE_UP:
				_monster[i].changeState(new monsterState(STATE::STATE_IDLE));
				break;

			case STATE::STATE_IDLE:
				_monster[i].changeState(new monsterState(STATE::STATE_DOWN));
				break;

			case STATE::STATE_DOWN:
				_monster[i].changeState(new monsterState(STATE::STATE_NONE));
				break;

			case STATE::STATE_DAMAGED:
				_monster[i].changeState(new monsterState(STATE::STATE_DAMAGEDDOWN));
				break;

			case STATE::STATE_DAMAGEDDOWN:
				_monster[i].changeState(new monsterState(STATE::STATE_NONE));
				break;

			default:
				break;
			}
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MONTER_MAX; i++)
		{
			if (PtInRect(&_monster[i].boundingBox(), _ptMouse) && 
				_monster[i].getMyState()->getStateInfo() != STATE::STATE_NONE &&
				_monster[i].getMyState()->getStateInfo() != STATE::STATE_DAMAGED &&
				_monster[i].getMyState()->getStateInfo() != STATE::STATE_DAMAGEDDOWN)
			{
				_monster[i].changeState(new monsterState(STATE::STATE_DAMAGED));

				//킬수 증가
				_killCount++;
			}
		}
	}

	_count++;

	//캐릭터 이미지 프레임을 계속 돌려라
	if (_count % 60 == 0)
	{
		_secound++;

		//틀린표시 2초후에 삭제	(현재 프레임을 별도로 관리하지않아 엉터리)

		if (_secound >= 3)
		{
			int idx = RND->getInt(MONTER_MAX - 1);
			if (_monster[idx].getMyState()->getStateInfo() == STATE::STATE_NONE)
			{
				_monster[idx].changeState(new monsterState(STATE::STATE_UP));
			}
			_secound = 0;
		}
		_count = 0;
	}

	//상태값 업데이트 끝나면 상태값들 위치 재설정
	initMonsterPoint();
	
}

void gameStudy::render(HDC hdc)
{
	//백버퍼에서 뿌려준다 (이건 렌더에 그냥 놔둘것)
	HDC backDC = this->getBackBuffer()->getMemDC();

	//맵이미지 (이것두 렌더에 그냥 놔둘것)
	//_mapImage->render(backDC, 0, 0); //백버퍼에 그림을 그리는 시작위치 0, 0에서 부터 그려라

	//백그라운드 이미지
	_bgImage->render(backDC, 0, 0); //백그라운드 이미지또한 그리는 시작위치는 0, 0임
	
	for (int i = 0; i < MONTER_MAX; i++)
	{
		_monster[i].getMyState()->frameRender(backDC,
			static_cast<int>(_monster[i].getMyState()->getX()), static_cast<int>(_monster[i].getMyState()->getY()),
			_monster[i].getMyState()->getFrameX(), _monster[i].getMyState()->getFrameY());
	}

	//백버퍼 내용을 hdc에 그린다 (이것두 렌더에 그냥 놔둘것)
	this->getBackBuffer()->render(hdc, 0, 0); //당근 이것도 마찬가지겠지?

	
	// score 텍스트 표시
	WCHAR str[20] = L"";
	wsprintf(str, L"%d", _killCount);
	TextOut(hdc, 300, 35, str, lstrlen(str));

	//SAFE_DELETE(str);
}

void gameStudy::initMonsterPoint(void)
{
	_monster[0].getMyState()->setX(80);
	_monster[0].getMyState()->setY(20);

	_monster[1].getMyState()->setX(280);
	_monster[1].getMyState()->setY(20);

	_monster[2].getMyState()->setX(500);
	_monster[2].getMyState()->setY(20);

	_monster[3].getMyState()->setX(80);
	_monster[3].getMyState()->setY(150);

	_monster[4].getMyState()->setX(280);
	_monster[4].getMyState()->setY(150);

	_monster[5].getMyState()->setX(500);
	_monster[5].getMyState()->setY(150);

	_monster[6].getMyState()->setX(80);
	_monster[6].getMyState()->setY(300);

	_monster[7].getMyState()->setX(280);
	_monster[7].getMyState()->setY(300);

	_monster[8].getMyState()->setX(500);
	_monster[8].getMyState()->setY(300);
}