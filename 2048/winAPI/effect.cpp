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
	//이펙트 돌고있냐?
	_isRunning = false;

	//이미지 넣어준다
	_effectImage = effectImage;

	//이펙트 경과시간
	_elapsedTime = elapsedTime;

	//이미지 애니메이션 객체가 없으면 생성한다
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
	//활성화 안되어 있으면 실행되지 않는다
	if (!_isRunning) return;
	_effectAnimation->frameUpdate(_elapsedTime);

	if (!_effectAnimation->isPlay()) killEffect();
}

void effect::render(void)
{
	//활성화 안되어 있으면 실행되지 않는다
	if (!_isRunning) return;

	_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
}

//이펙트 시작
void effect::startEffect(int x, int y)
{
	//정보가 초기화 되어있지 않다면 실행하지 않는닫
	if (!_effectImage || !_effectAnimation) return;

	//매개변수의 위치를 effect의 중앙으로 본다
	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}

//이펙트 살인
void effect::killEffect(void)
{
	_isRunning = false;
}

