#pragma once
#include "gameNode.h"
#include "stage.h"

class gameScene : public gameNode
{
public:
	gameScene();
	~gameScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

private:
	stage* _stage;

};

