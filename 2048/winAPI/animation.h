
#pragma once

#include <vector>

class animation
{
public:
	typedef std::vector<POINT> arrFrameList;
	typedef std::vector<int> arrPlayList;

private:
	int _frameNum;	//프레임 수...
	
	arrFrameList _vFrameList;	//프레임 위치 리스트..
	arrPlayList _vPlayList;		//플레이 리스트

	int _frameWidth;			//프레임 가로크기
	int _frameHeight;			//프레임 세로크기

	BOOL _loop;					//루프냐?
	float _frameUpdateSec;		//프레임 업데이트 초..
	float _elapsedSec;			//프레임 지난 초..

	DWORD _nowPlayIdx;			//현재 플레이 인덱스 번호..
	BOOL _play;					//플레이냐?

public:
	HRESULT init (int totalW, int totalH, int frameW, int frameH);

	void setDefPlayFrame(BOOL reverse = false, BOOL loop = false);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = false);
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = false);

	void setFPS(int framePerSec);		//초당 갱신 횟수
	void frameUpdate(float elpasedTime);

	void start(void);			//플레이 시작..
	void stop(void);			//정지
	void pause(void);			//일시정지..
	void resume(void);			//다시 시작..

	//플레이냐?
	inline BOOL isPlay(void) {return _play;}

	//프레임 위치 얻어온다
	inline POINT getFramePos(void) {return _vFrameList[_vPlayList[_nowPlayIdx]];}

	inline int getFrameWidth(void) {return _frameWidth;}
	inline int getFrameHeight(void) {return _frameHeight;}

	animation(void);
	~animation(void);
};


