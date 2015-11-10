#pragma once
#include "image.h"

enum STATE{ STATE_NONE, STATE_UP, STATE_IDLE, STATE_DOWN, STATE_DAMAGED, STATE_DAMAGEDDOWN };

class monsterState : public image
{
public:	
	monsterState(STATE state);

	~monsterState();

	virtual void update(void);

	const bool getIsStop() const;
	const STATE getStateInfo() const;

private:
	monsterState();

	int	_count;
	bool _bStop;
	STATE _state;
	int _secound;
};

class monster
{
public:
	monster();
	~monster();

	void changeState(monsterState* state);
	monsterState* getMyState() const;
	const RECT boundingBox() const;


private:
	monsterState* _nowState;
};

