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

	//ĳ���� �������� ������ ���� ����
	_count = 0;
	_frameX = 0;


	return S_OK;
}

//�����Ҵ� �Ѱ��� ���⼭ ����� ������ (�̹����� �� ���������~~)
void gameStudy::release(void)
{
	gameNode::release();
	
	//�̹��� �޸𸮿��� ����
	//SAFE_DELETE(_mapImage);
	SAFE_DELETE(_bgImage);

	//����ڽ��迭 �޸𸮿��� ����
	SAFE_DELETE_ARRAY(_bingoBox1);
	SAFE_DELETE_ARRAY(_bingoBox2);
	
	//����ǥ�õ� �̹����� �޸𸮿��� ����
	for (image*& pTemp : _vBingos)
	{
		SAFE_DELETE(pTemp);
	}

	// ���� ���� ����
	_vBingos.clear();
}

//�������� �ϴ� �ڵ��...
void gameStudy::update(void)
{
	gameNode::update();
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < BINGOMAX; i++)
		{
			//üũ���� ���°��� �����ϸ� üũ
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

				//üũ�ߴٸ� ����Ż��
				break;
			}
			//üũ�Ұ� ���ٸ� Ʋ�� ǥ��
			else if (i == BINGOMAX - 1)
			{
				_lMisses.push_back(new image);
				_lMisses.back()->init(L"ImageResource/miss.bmp", 50, 50, true, RGB(255, 0, 255));
				_lMisses.back()->setCenter(static_cast<float>(_ptMouse.x), static_cast<float>(_ptMouse.y));
			}
		}
	}

	_count++;

	//ĳ���� �̹��� �������� ��� ������
	if (_count % 60 == 0)
	{
		_secound++;

		//Ʋ��ǥ�� 2���Ŀ� ����	(���� �������� ������ ���������ʾ� ���͸�)
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
	//����ۿ��� �ѷ��ش� (�̰� ������ �׳� ���Ѱ�)
	HDC backDC = this->getBackBuffer()->getMemDC();

	//���̹��� (�̰͵� ������ �׳� ���Ѱ�)
	//_mapImage->render(backDC, 0, 0); //����ۿ� �׸��� �׸��� ������ġ 0, 0���� ���� �׷���

	//��׶��� �̹���
	_bgImage->render(backDC, 0, 0); //��׶��� �̹������� �׸��� ������ġ�� 0, 0��
	
	//üũ �̹���
	for (image*& pTemp : _vBingos)
	{
		pTemp->render(backDC);
	}

	//Ʋ��ǥ�� �̹���
	for (image*& pTemp : _lMisses)
	{
		pTemp->render(backDC);
	}

	//���������� false�� ���ٸ� ���̹���
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

	//����� ������ hdc�� �׸��� (�̰͵� ������ �׳� ���Ѱ�)
	this->getBackBuffer()->render(hdc, 0, 0); //��� �̰͵� ������������?
}
