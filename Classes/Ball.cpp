#include "Ball.h"
Ball::Ball()
{
	directionunitx = 0;
	directionunity = 0;
	moveSpeed = 150;
}
Ball::~Ball()
{


}
bool Ball::init()
{
	return true;
}

int Ball::getMoveSpeed()
{
	return moveSpeed;
}

void Ball::setBallradius(int r)
{
	this->ballradius = r;

}

int Ball::getBallradius()
{
	return ballradius;

}

Ball* Ball::create(const char* picFilename)
{
	Ball* sprite = new Ball();
	if (sprite&&sprite->initWithFile(picFilename))
	{

		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

