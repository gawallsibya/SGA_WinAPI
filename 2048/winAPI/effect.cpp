#include "StdAfx.h"
#include "effect.h"
#include "image.h"
#include "animation.h"

effect::effect(void) : _effectImage(NULL), _effectAnimation(NULL), _isRunning(false), _x(0), _y(0)
{
}

effect::~effect(void)
{
}

HRESULT effect::init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	//����Ʈ �����ֳ�?
	_isRunning = false;

	//�̹��� �־��ش�
	_effectImage = effectImage;

	//����Ʈ ����ð�
	_elapsedTime = elapsedTime;

	//�̹��� �ִϸ��̼� ��ü�� ������ �����Ѵ�
	if (!_effectAnimation) _effectAnimation = new animation;

	_effectAnimation->init(_effectImage->getWidth(),
		_effectImage->getHeight(), _effectImage->getFrameWidth(),
		_effectImage->getFrameHeight());
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();

	return S_OK;
}

void effect::release(void)
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void effect::update(void)
{
	//Ȱ��ȭ �ȵǾ� ������ ������� �ʴ´�
	if (!_isRunning) return;
	_effectAnimation->frameUpdate(_elapsedTime);

	if (!_effectAnimation->isPlay()) killEffect();
}

void effect::render(void)
{
	//Ȱ��ȭ �ȵǾ� ������ ������� �ʴ´�
	if (!_isRunning) return;

	_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
}

//����Ʈ ����
void effect::startEffect(int x, int y)
{
	//������ �ʱ�ȭ �Ǿ����� �ʴٸ� �������� �ʴ´�
	if (!_effectImage || !_effectAnimation) return;

	//�Ű������� ��ġ�� effect�� �߾����� ����
	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}

//����Ʈ ����
void effect::killEffect(void)
{
	_isRunning = false;
}

