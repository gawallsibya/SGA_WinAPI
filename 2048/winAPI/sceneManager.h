#pragma once
#include "singletonbase.h"
#include <map>
#include <string>

class gameNode;

using namespace std;

class sceneManager : public singletonBase <sceneManager>
{
public:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	static gameNode* _currentScene;	//ÇöÀç¾À
	static gameNode* _loadScene;	//·Îµù¾À
	static gameNode* _readyScene;	//±³Ã¼ ´ë±â ÁßÀÎ ¾À

	mSceneList _mSceneList;
	mSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//¾À Ãß°¡~~
	gameNode* addScene(string sceneName, gameNode* scene);

	//·Îµù¾À Ãß°¡~~
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//¾ÀÃ¼ÀÎÁö
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);
	
	friend DWORD CALLBACK loadingScene(LPVOID prc);

	sceneManager(void);
	~sceneManager(void);
};
