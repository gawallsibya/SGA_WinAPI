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

//동적할당 한것은 여기서 지우고 나가셈 (이미지들 다 삭제해줘랑~~)
void gameStudy::release(void)
{
	gameNode::release();

	//이미지 메모리에서 해제
	SAFE_DELETE(_pMapImage);

	for (cellInfo*& pTemp : _vCells)
	{
		SAFE_DELETE(pTemp);
	}
	_vCells.clear();
}

//움직여야 하는 코드들...
void gameStudy::update(void)
{
	gameNode::update();
	
	_count++;
	if (_count % (60 / 30) == 0)
	{
		if (_bReady)
		{
			_secound++;

			//3초동안 섞는다
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
	//백버퍼에서 뿌려준다 (이건 렌더에 그냥 놔둘것)
	HDC backDC = this->getBackBuffer()->getMemDC();

	//맵이미지 (이것두 렌더에 그냥 놔둘것)
	//_mapImage->render(backDC, 0, 0); //백버퍼에 그림을 그리는 시작위치 0, 0에서 부터 그려라

	//백그라운드 이미지
	//_pMapImage->render(backDC, 0, 0); //백그라운드 이미지또한 그리는 시작위치는 0, 0임

	int idx = 0;
	for (int i = 0; i < CELL_COUNT; i++)
	{
		for (int j = 0; j < CELL_COUNT; j++)
		{
			_pMapImage->frameRender(backDC,
			j * CELL_WIDTH,
			i * CELL_HEIGHT,
			_vCells.at(idx)->frameX, _vCells.at(idx)->frameY);

			// 네모그리기 // 정답 아닐때는 마지막 네모는 검은색
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


	//백버퍼 내용을 hdc에 그린다 (이것두 렌더에 그냥 놔둘것)
	this->getBackBuffer()->render(hdc, 0, 0); //당근 이것도 마찬가지겠지?
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
	// 맞춤여부 검사
	for (int i = 0; i < CELL_COUNT*CELL_COUNT - 1; i++)
	{
		if (_vCells.at(i)->myIdx != i)
		{
			return false;
		}
	}
	return true;
}

