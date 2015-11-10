#pragma once

class block;
class unit
{
public:
	unit();
	~unit();

	void init(int x, int y, int width, int height);
	void render(HDC hdc);
	void update();
	void release();

	void setRndNumber();

	void setPos(int x, int y);
	POINT getPos();

	void setNumber(int num);
	int getNumber();

	void setMyBlock(block* myBlock);
	block* getMyBlock();

private:
	image* _img;
	block* _myBlock;

	int _x;
	int _y;
	int _width;
	int _height;

	int _number;
	int _speed;
	int _frameX;
};

