#pragma once
#include "gameNode.h"

class gameOverScene : public gameNode
{
public:
	gameOverScene();
	~gameOverScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

private:
	image* _img;

};

