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
	//CREATE_FUNC(MainMenu); //����ΪcreateScene

	static int brickwidth;  //ÿ��ש����һ��
private:
	
	int BrickType; //��ͬ��ש��
//	int Positionx;
	//int Positiony;
	int attackedTime;
	bool brickexit;



};