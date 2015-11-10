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
	_bgImage->init(L"ImageResource/searchMap1.bmp", 960, 720);
	
	_endImage = new image;
	_endImage->init(L"ImageResource/end.bmp", 960, 720);

	_bingoBox1 = new BINGO_BOX[BINGOMAX];
	_bingoBox1[0].init(865, 215, 925, 275);
	_bingoBox1[1].init(615, 30, 675, 90);
	_bingoBox1[2].init(585, 285, 660, 330);
	_bingoBox1[3].init(360, 90, 440, 130);
	_bingoBox1[4].init(330, 175, 400, 220);
	_bingoBox1[5].init(130, 140, 180, 180);
	_bingoBox1[6].init(50, 90, 215, 150);

	_bingoBox2 = new BINGO_BOX[BINGOMAX];
	_bingoBox2[0].init(865, 575, 925, 635);
	_bingoBox2[1].init(615, 390, 675, 450);
	_bingoBox2[2].init(585, 645, 660, 690);
	_bingoBox2[3].init(360, 450, 440, 490);
	_bingoBox2[4].init(330, 535, 400, 580);
	_bingoBox2[5].init(130, 500, 180, 540);
	_bingoBox2[6].init(50, 450, 215, 510);

	//캐릭터 프레임을 돌리기 위한 변수
	_count = 0;
	_frameX = 0;


	return S_OK;
}

//동적할당 한것은 여기서 지우고 나가셈 (이미지들 다 삭제해줘랑~~)
void gameStudy::release(void)
{
	gameNode::release();
	
	//이미지 메모리에서 해제
	//SAFE_DELETE(_mapImage);
	SAFE_DELETE(_bgImage);

	//빙고박스배열 메모리에서 해제
	SAFE_DELETE_ARRAY(_bingoBox1);
	SAFE_DELETE_ARRAY(_bingoBox2);
	
	//빙고표시된 이미지들 메모리에서 해제
	for (image*& pTemp : _vBingos)
	{
		SAFE_DELETE(pTemp);
	}

	// 벡터 공간 해제
	_vBingos.clear();
}

//움직여야 하는 코드들...
void gameStudy::update(void)
{
	gameNode::update();
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < BINGOMAX; i++)
		{
			//체크한적 없는곳을 선택하면 체크
			if (!_bingoBox1[i].isCheck &&
				PtInRect(&_bingoBox1[i].bingoBundingBox, _ptMouse) ||
				PtInRect(&_bingoBox2[i].bingoBundingBox, _ptMouse))
			{
				_bingoBox1[i].isCheck = true;
				_bingoBox2[i].isCheck = true;

				_vBingos.push_back(new image);
				_vBingos.back()->init(L"ImageResource/bingo.bmp", 50, 50, true, RGB(255, 0, 255));
				_vBingos.back()->setCenter(_bingoBox1[i].GetCenter().x, _bingoBox1[i].GetCenter().y);

				_vBingos.push_back(new image);
				_vBingos.back()->init(L"ImageResource/bingo.bmp", 50, 50, true, RGB(255, 0, 255));
				_vBingos.back()->setCenter(_bingoBox1[i].GetCenter().x, _bingoBox2[i].GetCenter().y);

				//체크했다면 루프탈출
				break;
			}
			//체크할게 없다면 틀림 표시
			else if (i == BINGOMAX - 1)
			{
				_lMisses.push_back(new image);
				_lMisses.back()->init(L"ImageResource/miss.bmp", 50, 50, true, RGB(255, 0, 255));
				_lMisses.back()->setCenter(static_cast<float>(_ptMouse.x), static_cast<float>(_ptMouse.y));
			}
		}
	}

	_count++;

	//캐릭터 이미지 프레임을 계속 돌려라
	if (_count % 60 == 0)
	{
		_secound++;

		//틀린표시 2초후에 삭제	(현재 프레임을 별도로 관리하지않아 엉터리)
		if (_secound >= 2)
		{
			if (_lMisses.size() != 0)
			{
				SAFE_DELETE(_lMisses.front());
				_lMisses.remove(_lMisses.front());
			}
			_secound = 0;
		}
		_count = 0;
	}

}

void gameStudy::render(HDC hdc)
{
	//백버퍼에서 뿌려준다 (이건 렌더에 그냥 놔둘것)
	HDC backDC = this->getBackBuffer()->getMemDC();

	//맵이미지 (이것두 렌더에 그냥 놔둘것)
	//_mapImage->render(backDC, 0, 0); //백버퍼에 그림을 그리는 시작위치 0, 0에서 부터 그려라

	//백그라운드 이미지
	_bgImage->render(backDC, 0, 0); //백그라운드 이미지또한 그리는 시작위치는 0, 0임
	
	//체크 이미지
	for (image*& pTemp : _vBingos)
	{
		pTemp->render(backDC);
	}

	//틀린표시 이미지
	for (image*& pTemp : _lMisses)
	{
		pTemp->render(backDC);
	}

	//마지막까지 false가 없다면 끝이미지
	for (int i = 0; i < BINGOMAX; i++)
	{
		if (_bingoBox1[i].isCheck == false)
		{
			break;
		}
		else if (i == BINGOMAX - 1)
		{
			_endImage->render(backDC);
		}
	}

	//백버퍼 내용을 hdc에 그린다 (이것두 렌더에 그냥 놔둘것)
	this->getBackBuffer()->render(hdc, 0, 0); //당근 이것도 마찬가지겠지?
}
