#include "Brick.h"
Brick::Brick(int type)   //1 ,2 ,3 ,4,5
{
	/*
	this->Positionx = x;
	this->Positiony = y;
	*/
	this->brickexit = true; //����Ǵ��ڵ�
	this->attackedTime = 0; //���������Ϊ0
	this->BrickType = type;
}
Brick::~Brick()
{


}/*
int Brick::getBrickX()
{

	return Positionx;
}
int Brick::getBrickY()
{
	return Positiony;
}*/
void Brick::setBrickWidth(int w)
{
	brickwidth = w;
}
int Brick::getBrickWidth()
{

	return brickwidth;
}
int Brick::getBrickType()
{

	return BrickType;

}

bool Brick::isExit()
{
	return brickexit;
}
void Brick::addAttackedTime()
{
	this->attackedTime++;
}
int Brick::getAttackedTime()
{
	return attackedTime;
}

void Brick::setBrickExitFlag(int f)
{
	if (f == 0) brickexit = false;
	else
	{
		 //Ĭ��Ϊtrue ����Ҫ���θ�ֵ
	}

}
int Brick::getBrickBloodValue()
{
	return this->BrickType;

}


Brick* Brick::create(const char* picFilename,int type)
{

	Brick* sprite = new Brick(type);
	if (sprite&& sprite->initWithFile(picFilename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}