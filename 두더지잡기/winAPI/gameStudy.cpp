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

	//��ġ ����
	initMonsterPoint();

	_count = 0;
	_frameX = 0;
	_killCount = 0;

	return S_OK;
}

//�����Ҵ� �Ѱ��� ���⼭ ����� ������ (�̹����� �� ���������~~)
void gameStudy::release(void)
{
	gameNode::release();
	
	//�̹��� �޸𸮿��� ����
	//SAFE_DELETE(_mapImage);

	SAFE_DELETE(_bgImage);
}

//�������� �ϴ� �ڵ��...
void gameStudy::update(void)
{
	gameNode::update();

	//���°� ��ȭ ������Ʈ
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

				//ų�� ����
				_killCount++;
			}
		}
	}

	_count++;

	//ĳ���� �̹��� �������� ��� ������
	if (_count % 60 == 0)
	{
		_secound++;

		//Ʋ��ǥ�� 2���Ŀ� ����	(���� �������� ������ ���������ʾ� ���͸�)

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

	//���°� ������Ʈ ������ ���°��� ��ġ �缳��
	initMonsterPoint();
	
}

void gameStudy::render(HDC hdc)
{
	//����ۿ��� �ѷ��ش� (�̰� ������ �׳� ���Ѱ�)
	HDC backDC = this->getBackBuffer()->getMemDC();

	//���̹��� (�̰͵� ������ �׳� ���Ѱ�)
	//_mapImage->render(backDC, 0, 0); //����ۿ� �׸��� �׸��� ������ġ 0, 0���� ���� �׷���

	//��׶��� �̹���
	_bgImage->render(backDC, 0, 0); //��׶��� �̹������� �׸��� ������ġ�� 0, 0��
	
	for (int i = 0; i < MONTER_MAX; i++)
	{
		_monster[i].getMyState()->frameRender(backDC,
			static_cast<int>(_monster[i].getMyState()->getX()), static_cast<int>(_monster[i].getMyState()->getY()),
			_monster[i].getMyState()->getFrameX(), _monster[i].getMyState()->getFrameY());
	}

	//����� ������ hdc�� �׸��� (�̰͵� ������ �׳� ���Ѱ�)
	this->getBackBuffer()->render(hdc, 0, 0); //��� �̰͵� ������������?

	
	// score �ؽ�Ʈ ǥ��
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