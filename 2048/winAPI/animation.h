
#pragma once

#include <vector>

class animation
{
public:
	typedef std::vector<POINT> arrFrameList;
	typedef std::vector<int> arrPlayList;

private:
	int _frameNum;	//������ ��...
	
	arrFrameList _vFrameList;	//������ ��ġ ����Ʈ..
	arrPlayList _vPlayList;		//�÷��� ����Ʈ

	int _frameWidth;			//������ ����ũ��
	int _frameHeight;			//������ ����ũ��

	BOOL _loop;					//������?
	float _frameUpdateSec;		//������ ������Ʈ ��..
	float _elapsedSec;			//������ ���� ��..

	DWORD _nowPlayIdx;			//���� �÷��� �ε��� ��ȣ..
	BOOL _play;					//�÷��̳�?

public:
	HRESULT init (int totalW, int totalH, int frameW, int frameH);

	void setDefPlayFrame(BOOL reverse = false, BOOL loop = false);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = false);
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = false);

	void setFPS(int framePerSec);		//�ʴ� ���� Ƚ��
	void frameUpdate(float elpasedTime);

	void start(void);			//�÷��� ����..
	void stop(void);			//����
	void pause(void);			//�Ͻ�����..
	void resume(void);			//�ٽ� ����..

	//�÷��̳�?
	inline BOOL isPlay(void) {return _play;}

	//������ ��ġ ���´�
	inline POINT getFramePos(void) {return _vFrameList[_vPlayList[_nowPlayIdx]];}

	inline int getFrameWidth(void) {return _frameWidth;}
	inline int getFrameHeight(void) {return _frameHeight;}

	animation(void);
	~animation(void);
};


