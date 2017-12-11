#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Baffle :public Sprite
{
public:
	Baffle();
	~Baffle();
	virtual bool init();
	int getMoveSpeed();
	void setMoveDirection(int x);
	int getMoveDirection();
	void setLength(int);
	int getLength();
	void setHeight(int);
	int getHeight();
	//int getxiangsuX();
	//int getxiangsuY();
	//int getLength();
	static Baffle* create(const char*);

private:
	//const int xiangsuX = 80;
	//const int xiangsuY = 56;
	int moveSpeed;
	int moveDirection;   //1���ң�-1����
	int length; //���峤��
	int height; //����߶�
	int positiony;
};