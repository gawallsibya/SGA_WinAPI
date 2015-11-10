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

	//����Ʈ�� ��� �־�� ���͸� �˻�
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

	//����Ʈ�� ��� �־�� ���͸� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű�� �˻��Ѵ�
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

	//����Ʈ�� ��� �־�� ���͸� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű�� �˻��Ѵ�
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
	arrEffects vEffectBuffer;	 //����Ʈ ���۸� ��´�
	arrEffect mArrEffect;		//Ű���� ���� ����Ʈ�� ��´�

	//��ϵ� �̹����� �Ŵ����� ������...
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else //������...
	{
		img = IMAGEMANAGER->addFrameImage(imageName, imageName, 0, 0, imageWidth,
			imageHeight, effectWidth, effectHeight, true, RGB(255, 0, 255));
	}

	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps, elapsed);
	}

	//����Ʈ ���۸� �ʿ� ��´�
	mArrEffect.insert(make_pair(effectName, vEffectBuffer));

	//Ű���� ���۸� ���� ���� �ٽ� _vTotalEffects�� �ִ´�
	_vTotalEffects.push_back(mArrEffect);
}

void effectManager::play(string effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���͸� �˻��Ѵ�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű�� �˻��Ѵ�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����Ʈ �̸��� ���� ���� ������ ���� ������ �Ѿ��
			if (!(mIter->first == effectName)) break;

			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� �����Ѵ�
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
