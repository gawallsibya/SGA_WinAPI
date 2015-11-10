#include "stdafx.h"
#include "stage.h"


stage::stage()
{
}


stage::~stage()
{
}


void stage::init(void)
{
	_unitCount = 0;

	for (int i = 0; i < BLOCK_HEIGHT; i++)
	{
		for (int j = 0; j < BLOCK_WIDTH; j++)
		{
			_block[i][j].init(100 * j + 20*j + 20, 100 * i + 20*i + 20, 100, 100);
		}
	}
	// 숫자 2개 생성.
	RndCreateUnit();
	RndCreateUnit();
}

void stage::release(void)
{
	memset(*_block, 0, sizeof(block) * (BLOCK_WIDTH * BLOCK_HEIGHT));
	for (unit* temp : lUnitList)
	{
		SAFE_DELETE(temp);
	}
	lUnitList.clear();
	vNullBlockList.clear();
	_unitCount = 0;
}

void stage::update(void)
{
	commendUpdate();

	for (unit* temp : lUnitList)
	{
		temp->update();
	}

	// 안만들어지면 게임을 끝내겠다!
	if (_unitCount == BLOCK_WIDTH * BLOCK_HEIGHT)
	{
		SCENEMANAGER->changeScene("gameOverScene");
		return;
	}

}

void stage::render(HDC hdc)
{
	for (int i = 0; i < BLOCK_HEIGHT; i++)
	{
		for (int j = 0; j < BLOCK_WIDTH; j++)
		{
			_block[i][j].render(hdc);
		}
	}

	for (unit* temp : lUnitList)
	{
		temp->render(hdc);
	}
}

bool stage::isUnitHandling(block* prevBlock, block* nextBlock)
{
	if (prevBlock->getUnit() != nullptr)
	{
		// 이동하려는 블럭에 숫자가 없을때.
		if (nextBlock->getUnit() == nullptr)
		{
			prevBlock->getUnit()->setMyBlock(nextBlock);
			nextBlock->setUnit(prevBlock->getUnit());
			prevBlock->setUnit(nullptr);
			return true;
		}
		// 이동하려는 블럭에 숫자가 있을때.
		else if (prevBlock->getUnit()->getNumber() == nextBlock->getUnit()->getNumber())
		{
			nextBlock->getUnit()->setNumber(nextBlock->getUnit()->getNumber() + prevBlock->getUnit()->getNumber());
			lUnitList.remove(prevBlock->getUnit());
			prevBlock->deleteUnit();
			_unitCount--;
			return true;
		}
	}
	return false;
}

void stage::commendUpdate()
{
	bool bHandled = false;
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		for (int i = 0; i < BLOCK_HEIGHT; i++)
		{
			for (int j = 1; j < BLOCK_WIDTH; j++)
			{
				// 이동 가능한 블럭 체크 루프.
				for (int k = 0; j - k >= 1; k++)
				{
					// 다음칸에 숫자가 있으면 처리 후 루프 탈출, 없으면 루프 진행.
					if (_block[i][j - k - 1].getUnit() != nullptr)
					{
						if (isUnitHandling(&_block[i][j - k], &_block[i][j - k - 1]))
						{
							bHandled = true;
						}
						break;
					}
					else
					{
						if (isUnitHandling(&_block[i][j - k], &_block[i][j - k - 1]))
						{
							bHandled = true;
						}
					}
				}
			}
		}
		if (bHandled) RndCreateUnit();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		for (int i = 0; i < BLOCK_HEIGHT; i++)
		{
			for (int j = BLOCK_WIDTH - 2; j >= 0; j--)
			{
				// 이동 가능한 블럭 체크 루프.
				for (int k = 0; k + j <= BLOCK_WIDTH - 2; k++)
				{
					// 다음칸에 숫자가 있으면 처리 후 루프 탈출, 없으면 루프 진행.
					if (_block[i][j + k + 1].getUnit() != nullptr)
					{
						if (isUnitHandling(&_block[i][j + k], &_block[i][j + k + 1]))
						{
							bHandled = true;
						}
						break;
					}
					else
					{
						if (isUnitHandling(&_block[i][j + k], &_block[i][j + k + 1]))
						{
							bHandled = true;
						}
					}
				}

			}
		}
		if (bHandled) RndCreateUnit();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		for (int i = 1; i < BLOCK_HEIGHT; i++)
		{
			for (int j = 0; j < BLOCK_WIDTH; j++)
			{
				// 이동 가능한 블럭 체크 루프.
				for (int k = 0; i - k >= 1; k++)
				{
					// 다음칸에 숫자가 있으면 처리 후 루프 탈출, 없으면 루프 진행.
					if (_block[i - k - 1][j].getUnit() != nullptr)
					{
						if (isUnitHandling(&_block[i - k][j], &_block[i - k - 1][j]))
						{
							bHandled = true;
						}
						break;
					}
					else
					{
						if (isUnitHandling(&_block[i - k][j], &_block[i - k - 1][j]))
						{
							bHandled = true;
						}
					}
				}

			}
		}
		if (bHandled) RndCreateUnit();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		for (int i = BLOCK_HEIGHT - 2; i >= 0; i--)
		{
			for (int j = 0; j < BLOCK_WIDTH; j++)
			{
				// 이동 가능한 블럭 체크 루프.
				for (int k = 0; k + i <= BLOCK_HEIGHT - 2; k++)
				{
					// 다음칸에 숫자가 있으면 처리 후 루프 탈출, 없으면 루프 진행.
					if (_block[i + k + 1][j].getUnit() != nullptr)
					{
						if (isUnitHandling(&_block[i + k][j], &_block[i + k + 1][j]))
						{
							bHandled = true;
						}
						break;
					}
					else
					{
						if (isUnitHandling(&_block[i + k][j], &_block[i + k + 1][j]))
						{
							bHandled = true;
						}
					}
				}
			}
		}
		if (bHandled) RndCreateUnit();
	}
}

void stage::RndCreateUnit()
{
	vNullBlockList.clear();
	for (int i = 0; i < BLOCK_HEIGHT; i++)
	{
		for (int j = 0; j < BLOCK_WIDTH; j++)
		{
			if (_block[i][j].getUnit() == nullptr)
			{
				vNullBlockList.push_back(&_block[i][j]);
			}
		}
	}
	
	for (block* temp : vNullBlockList)
	{
		int rnd = RND->getInt(8);
		if (rnd == 7)
		{
			unit* pUnit = new unit;
			pUnit->init(temp->getPos().x, temp->getPos().y, temp->getSize().cx, temp->getSize().cy);
			pUnit->setRndNumber();
			pUnit->setMyBlock(temp);
			temp->setUnit(pUnit);

			lUnitList.push_back(pUnit);
			_unitCount++;

			return;
		}
	}

	// 안생기면 자신을 다시 호출, 임의의 블럭에 하나를 생성할 때 까지.
	RndCreateUnit();
}