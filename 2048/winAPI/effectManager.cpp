#include "StdAfx.h"
#include "effectManager.h"
#include "effect.h"

effectManager::effectManager(void)
{
}

effectManager::~effectManager(void)
{
}

HRESULT effectManager::init(void)
{
	return S_OK;
}

void effectManager::release(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//이펙트를 모두 넣어둔 벡터를 검사
	vIter = _vTotalEffects.begin();
	for (vIter; vIter != _vTotalEffects.end(); ++vIter)
	{
		mIter = vIter->begin();
		for (;mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				iterEffects vArrIter = mIter->second.begin();
				for (vArrIter; vArrIter != mIter->second.end();)
				{
					if (mIter->second.size() != 0)
					{
						(*vArrIter)->release();
						delete *vArrIter;
						vArrIter = mIter->second.erase(vArrIter);
					}
					else ++vArrIter;
				}
				mIter->second.clear();
			}
			else
			{
				++mIter;
			}
		}
	}

	_vTotalEffects.clear();
}

void effectManager::update(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//이펙트를 모두 넣어둔 벡터를 검사
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//토탈이펙트 벡터 안에 있는 맵의 이펙트 키를 검사한다
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update();
			}
		}
	}
}

void effectManager::render(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//이펙트를 모두 넣어둔 벡터를 검사
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//토탈이펙트 벡터 안에 있는 맵의 이펙트 키를 검사한다
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}
}

void effectManager::addEffect(string effectName, const char* imageName,
	int imageWidth, int imageHeight, int effectWidth,
	int effectHeight, int fps, float elapsed, int buffer)
{
	image* img;
	arrEffects vEffectBuffer;	 //이펙트 버퍼를 담는다
	arrEffect mArrEffect;		//키값과 벡터 이펙트를 담는다

	//등록된 이미지가 매니져에 있으면...
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else //없으면...
	{
		img = IMAGEMANAGER->addFrameImage(imageName, imageName, 0, 0, imageWidth,
			imageHeight, effectWidth, effectHeight, true, RGB(255, 0, 255));
	}

	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps, elapsed);
	}

	//이펙트 버퍼를 맵에 담는다
	mArrEffect.insert(make_pair(effectName, vEffectBuffer));

	//키값과 버퍼를 담은 맵을 다시 _vTotalEffects에 넣는다
	_vTotalEffects.push_back(mArrEffect);
}

void effectManager::play(string effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//이펙트를 모두 넣어둔 벡터를 검사한다
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//토탈이펙트 벡터 안에 있는 맵의 이펙트 키를 검사한다
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//이펙트 이름을 비교해 같지 않으면 다음 맵으로 넘어간다
			if (!(mIter->first == effectName)) break;

			//이펙트 키와 일치하면 이펙트를 실행한다
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->startEffect(x, y);
				return;
			}
		}
	}
}
