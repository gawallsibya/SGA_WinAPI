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
	_pMapImage = new image;
	_pMapImage->init(L"ImageResource/map.bmp", 550, 550);
	
	_endImage = new image;
	_endImage->init(L"ImageResource/end.bmp", 550, 550);

	//2�����迭 �����
	_ppMapRects = new mapRect*[MAPSIZE_MAX];
	for (int i = 0; i < MAPSIZE_MAX; i++)
	{
		_ppMapRects[i] = new mapRect[MAPSIZE_MAX];
		memset(_ppMapRects[i], 0, sizeof(mapRect) * MAPSIZE_MAX);
	}

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			_ppMapRects[j][i].setCenter(32 + (27 * j), 32 + (27 * i));	// ��ǥ����
			_ppMapRects[j][i].stoneColor = STONECOLOR::STONE_NONE;	// ������
		}
	}
	
	_count = 0;
	_frameX = 0;
	_winner = WIN::NONE;

	_turn = PLAYER::P1;

	return S_OK;
}

//�����Ҵ� �Ѱ��� ���⼭ ����� ������ (�̹����� �� ���������~~)
void gameStudy::release(void)
{
	gameNode::release();

	//�̹��� �޸𸮿��� ����
	SAFE_DELETE(_pMapImage);

	for (image* pTemp : _vBlackStones)
	{
		SAFE_DELETE(pTemp);
	}
	_vBlackStones.clear();

	for (image* pTemp : _vWhiteStones)
	{
		SAFE_DELETE(pTemp);
	}
	_vWhiteStones.clear();

	for (int i = 0; i < 19; i++)
	{
		SAFE_DELETE_ARRAY(_ppMapRects);
	}
}

//�������� �ϴ� �ڵ��...
void gameStudy::update(void)
{
	gameNode::update();
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))	
	{
		switch (_turn)
		{
		case P1:
			if (!collisionMap())
			{
				int x = mousePointToMapPoint().x;
				int y = mousePointToMapPoint().y;
				
				if (_ppMapRects[x][y].stoneColor == STONECOLOR::STONE_NONE)
				{
					_ppMapRects[x][y].stoneColor = STONECOLOR::STONE_BLACK;
					dropStone(_vBlackStones, _ppMapRects[x][y].left, _ppMapRects[x][y].top, _ppMapRects[x][y].stoneColor);

					if (searchLine(x, y))
					{
						_winner = WIN::WIN_BLACK;
						_endImage->init(L"ImageResource/blackWin.bmp", 550, 550);
					}

					_turn = PLAYER::P2;
				}
			}
			break;
		case P2:
			if (!collisionMap())
			{
				int x = mousePointToMapPoint().x;
				int y = mousePointToMapPoint().y;

				if (_ppMapRects[x][y].stoneColor == STONECOLOR::STONE_NONE)
				{
					_ppMapRects[x][y].stoneColor = STONECOLOR::STONE_WHITE;
					dropStone(_vWhiteStones, _ppMapRects[x][y].left, _ppMapRects[x][y].top, _ppMapRects[x][y].stoneColor);

					if (searchLine(x, y))
					{
						_winner = WIN::WIN_WHITE;
						_endImage->init(L"ImageResource/whiteWin.bmp", 550, 550);
					}

					_turn = PLAYER::P1;
				}
			}
			break;
		default:
			break;
		}
	}	
}

void gameStudy::render(HDC hdc)
{
	//����ۿ��� �ѷ��ش� (�̰� ������ �׳� ���Ѱ�)
	HDC backDC = this->getBackBuffer()->getMemDC();

	//���̹��� (�̰͵� ������ �׳� ���Ѱ�)
	//_mapImage->render(backDC, 0, 0); //����ۿ� �׸��� �׸��� ������ġ 0, 0���� ���� �׷���

	//��׶��� �̹���
	_pMapImage->render(backDC, 0, 0); //��׶��� �̹������� �׸��� ������ġ�� 0, 0��
	
	for (image* pTemp : _vBlackStones)
	{
		pTemp->render(backDC);
	}

	for (image* pTemp : _vWhiteStones)
	{
		pTemp->render(backDC);
	}

	if (_winner != WIN::NONE)
	{
		_endImage->render(backDC);
	}

	//����� ������ hdc�� �׸��� (�̰͵� ������ �׳� ���Ѱ�)
	this->getBackBuffer()->render(hdc, 0, 0); //��� �̰͵� ������������?
}

bool gameStudy::collisionMap()
{
	int minX = _ppMapRects[0][0].left;
	int minY = _ppMapRects[0][0].top;
	int maxX = _ppMapRects[MAPSIZE_MAX - 1][0].right;
	int maxY = _ppMapRects[0][MAPSIZE_MAX - 1].bottom;

	// x�� �˻�
	if (minX > _ptMouse.x || maxX < _ptMouse.x)
	{
		return true;
	}
	// y�� �˻�
	if (minY > _ptMouse.y || maxY < _ptMouse.y)
	{
		return true;
	}
	// �浹 �������� false
	return false;
}

void gameStudy::dropStone(vector<stone*>& vStone, int x, int y, STONECOLOR color)
{
	vStone.push_back(new stone(color));

	vStone.back()->setX(static_cast<float>(x));
	vStone.back()->setY(static_cast<float>(y));
}

POINT gameStudy::mousePointToMapPoint()
{
	POINT p;
	p.x = _ptMouse.x - _ppMapRects[0][0].left;
	p.y = _ptMouse.y - _ppMapRects[0][0].top;

	p.x = p.x / 27;
	p.y = p.y / 27;

	return p;
}

bool gameStudy::searchLine(int x, int y)
{
	STONECOLOR stoneColor = _ppMapRects[x][y].stoneColor;
	int stack = 1;

	//������ �˻�
	for (int i = 1; i < 5; i++)
	{
		if (x - i >= 0 && stoneColor == _ppMapRects[x - i][y].stoneColor)
		{
			stack++;
		}
		if (x + i <= MAPSIZE_MAX - 1 && stoneColor == _ppMapRects[x + i][y].stoneColor)
		{
			stack++;
		}
	}

	if (stack == 5)
	{
		return true;
	}
	else
	{
		stack = 1;
	}

	//������ �˻�
	for (int i = 1; i < 5; i++)
	{
		if(y - i >= 0 && stoneColor == _ppMapRects[x][y - i].stoneColor)
		{
			stack++;
		}
		if (y + i <= MAPSIZE_MAX - 1 && stoneColor == _ppMapRects[x][y + i].stoneColor)
		{
			stack++;
		}
	}

	if (stack == 5)
	{
		return true;
	}
	else
	{
		stack = 1;
	}

	//�밢���� �˻�1
	for (int i = 1; i < 5; i++)
	{
		if (x - i >= 0 && y - i >= 0 && stoneColor == _ppMapRects[x - i][y - i].stoneColor)
		{
			stack++;
		}
		if (x + i <= MAPSIZE_MAX - 1 && y + i <= MAPSIZE_MAX - 1 && stoneColor == _ppMapRects[x + i][y + i].stoneColor)
		{
			stack++;
		}
	}

	if (stack == 5)
	{
		return true;
	}
	else
	{
		stack = 1;
	}

	//�밢���� �˻�2
	for (int i = 1; i < 5; i++)
	{
		if (x - i >= 0 && y + i <= MAPSIZE_MAX - 1 && stoneColor == _ppMapRects[x - i][y + i].stoneColor)
		{
			stack++;
		}
		if (x + i <= MAPSIZE_MAX - 1 && y - i >= 0 && stoneColor == _ppMapRects[x + i][y - i].stoneColor)
		{
			stack++;
		}
	}

	if (stack == 5)
	{
		return true;
	}
	else
	{
		stack = 1;
	}

	// 5��¥���� ������ fasle
	return false;
}