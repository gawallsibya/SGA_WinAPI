#pragma once

class unit;
class block 
{
public:
	block();
	~block();

	void init(int x, int y, int width, int height);
	void render(HDC hdc);
	void update();
	void release();

	void deleteUnit();

	inline unit* getUnit() { return _unit; }
	inline void setUnit(unit* pUnit) { _unit = pUnit; }
	
	inline POINT getPos() { POINT p = { _x, _y }; return p; }
	inline SIZE getSize() { SIZE s = { _width, _height }; return s; }
private:
	unit* _unit;

	int _x;
	int _y;
	int _width;
	int _height;

	int _idxX;
	int _idxY;
};

