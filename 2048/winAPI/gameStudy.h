#pragma once

#include "gameNode.h"

class gameStudy : public gameNode
{
private:


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	gameStudy(void);
	~gameStudy(void);
};
