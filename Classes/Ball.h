#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Ball :public Sprite
{
public:

	Ball();
	~Ball();
	virtual bool init();
	int getMoveSpeed();
	void setBallradius(int);
	int getBallradius();

	static Ball* create(const char*);

public:
	//方向
	double directionunitx;
	double directionunity;
private:
	int moveSpeed;
	int ballradius;

	bool rebouond;// 即碰到Brick 为false则不反弹

};