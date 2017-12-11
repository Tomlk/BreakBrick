#include "baffle.h"

Baffle::Baffle()
{

	this->moveSpeed = 20; //初始挡板移动速度
	this->length = 300;  //初始挡板长度
	this->moveDirection = 0; 
}
Baffle::~Baffle()
{


}
bool Baffle::init()
{
	return true;
}
int Baffle::getMoveSpeed()
{
	return moveSpeed;

}
int Baffle::getMoveDirection()
{
	return moveDirection;
}
void Baffle::setMoveDirection(int x)
{
	moveDirection = (x > 0 ? 1 : -1);
	//return (x>0? 1 : -1);
}
int Baffle::getLength()
{

	return length;
}

void Baffle::setLength(int x)
{
	length = x;
}
void Baffle::setHeight(int h)
{
	this->height = h;
}
int Baffle::getHeight()
{

	return height;
}
/*
int baffle::getxiangsux()
{
	return xiangsux;
}

int baffle::getxiangsuy()
{
	return xiangsuy;
}*/
Baffle* Baffle::create(const char*picFilename)
{
	Baffle* sprite = new Baffle();
	if (sprite&&sprite->initWithFile(picFilename))
	{

		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}