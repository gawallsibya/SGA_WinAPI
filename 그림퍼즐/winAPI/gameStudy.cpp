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
	_pMapImage->init(L"ImageResource/puzzleMap.bmp", 550, 475, CELL_COUNT, CELL_COUNT);

	int idx = 0;
	for (int i = 0; i < CELL_COUNT; i++)
	{
		for (int j = 0; j < CELL_COUNT; j++)
		{
			_vCells.push_back(new cellInfo);
			_vCells.back()->myIdx = idx;
			_vCells.back()->frameX = j;
			_vCells.back()->frameY = i;

			idx++;
		}
	}

	_endImage = new image;
	_endImage->init(L"ImageResource/end.bmp", 550, 550);

	_count = 0;
	_frameX = 0;
	
	_idx = (CELL_COUNT * CELL_COUNT) - 1;

	_bReady = false;
	_bStart = false;
	_bClear = false;

	

	return S_OK;
}

//�����Ҵ� �Ѱ��� ���⼭ ����� ������ (�̹����� �� ���������~~)
void gameStudy::release(void)
{
	gameNode::release();

	//�̹��� �޸𸮿��� ����
	SAFE_DELETE(_pMapImage);

	for (cellInfo*& pTemp : _vCells)
	{
		SAFE_DELETE(pTemp);
	}
	_vCells.clear();
}

//�������� �ϴ� �ڵ��...
void gameStudy::update(void)
{
	gameNode::update();
	
	_count++;
	if (_count % (60 / 30) == 0)
	{
		if (_bReady)
		{
			_secound++;

			//3�ʵ��� ���´�
			if (_secound > 3 * 30)
			{
				_secound = 0;
				_bReady = false;
				_bStart = true;
				_bClear = false;
			}
		}

		if (_bReady && !_bStart)
		{
			initPuzzle();
		}

		_count = 0;
	}

	if (isClear())
	{
		_bClear = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_bReady = true;
		_bStart = false;
		_bClear = false;
	}

	if (!_bClear)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_idx - CELL_COUNT >= 0)
			{
				changeCell(_vCells.at(_idx), _vCells.at(_idx - CELL_COUNT));
				_idx -= CELL_COUNT;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_idx + CELL_COUNT < static_cast<int>(_vCells.size()))
			{
				changeCell(_vCells.at(_idx), _vCells.at(_idx + CELL_COUNT));
				_idx += CELL_COUNT;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_idx - 1 >= 0)
			{
				changeCell(_vCells.at(_idx), _vCells.at(_idx - 1));
				_idx -= 1;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_idx + 1 < static_cast<int>(_vCells.size()))
			{
				changeCell(_vCells.at(_idx), _vCells.at(_idx + 1));
				_idx += 1;
			}
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
	//_pMapImage->render(backDC, 0, 0); //��׶��� �̹������� �׸��� ������ġ�� 0, 0��

	int idx = 0;
	for (int i = 0; i < CELL_COUNT; i++)
	{
		for (int j = 0; j < CELL_COUNT; j++)
		{
			_pMapImage->frameRender(backDC,
			j * CELL_WIDTH,
			i * CELL_HEIGHT,
			_vCells.at(idx)->frameX, _vCells.at(idx)->frameY);

			// �׸�׸��� // ���� �ƴҶ��� ������ �׸�� ������
			HBRUSH myBrush;
			if (_vCells.at(idx)->myIdx >= CELL_COUNT * CELL_COUNT - 1 && !_bClear)
			{
				myBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
			}
			else
			{
				myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			}
			
			HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, myBrush);

			Rectangle(backDC,
				j * CELL_WIDTH,
				i * CELL_HEIGHT,
				CELL_WIDTH + j * CELL_WIDTH,
				CELL_HEIGHT + i * CELL_HEIGHT);

			SelectObject(backDC, oldBrush);
			DeleteObject(myBrush);

			idx++;
		}
	}


	//����� ������ hdc�� �׸��� (�̰͵� ������ �׳� ���Ѱ�)
	this->getBackBuffer()->render(hdc, 0, 0); //��� �̰͵� ������������?
}

void gameStudy::changeCell(cellInfo* pCell1, cellInfo* pCell2)
{
	cellInfo temp = *pCell1;
	*pCell1 = *pCell2;
	*pCell2 = temp;
}

void gameStudy::initPuzzle()
{
	switch (RND->getFromIntTo(1, 4))
	{
	case 1:
		if (_idx - CELL_COUNT >= 0)
		{
			changeCell(_vCells.at(_idx), _vCells.at(_idx - CELL_COUNT));
			_idx -= CELL_COUNT;
		}
		break;

	case 2:
		if (_idx + CELL_COUNT < static_cast<int>(_vCells.size()))
		{
			changeCell(_vCells.at(_idx), _vCells.at(_idx + CELL_COUNT));
			_idx += CELL_COUNT;
		}
		break;

	case 3:
		if (_idx - 1 >= 0)
		{
			changeCell(_vCells.at(_idx), _vCells.at(_idx - 1));
			_idx -= 1;
		}
		break;

	case 4:
		if (_idx + 1 < static_cast<int>(_vCells.size()))
		{
			changeCell(_vCells.at(_idx), _vCells.at(_idx + 1));
			_idx += 1;
		}
		break;
	default:
		break;
	}
	
}

bool gameStudy::isClear()
{
	// ���㿩�� �˻�
	for (int i = 0; i < CELL_COUNT*CELL_COUNT - 1; i++)
	{
		if (_vCells.at(i)->myIdx != i)
		{
			return false;
		}
	}
	return true;
}

