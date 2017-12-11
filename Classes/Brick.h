#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Brick:public Sprite
{
public:

	Brick(int); //x,y, type
	~Brick();
	int getBrickX();
	int getBrickY();
	 void setBrickWidth(int);
	 bool isExit();
	 void addAttackedTime();
	 void setBrickExitFlag(int);



	 int getBrickBloodValue();
	 int getAttackedTime();
	int getBrickWidth();
	int getBrickType();
	static Brick* create(const char*, int);
	//CREATE_FUNC(MainMenu); //必须为createScene

	static int brickwidth;  //每个砖块宽度一样
private:
	
	int BrickType; //不同的砖块
//	int Positionx;
	//int Positiony;
	int attackedTime;
	bool brickexit;



};