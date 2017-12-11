#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "baffle.h"
#include "Brick.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;
class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	virtual bool init();//初始化
	//添加砖块初始化函数
	void blockplan1();


	//触屏函数
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	static Scene* createScene();
	//定时器
	virtual void update(float);

	Point TargetPoint( double directionx, double directiony);

	CREATE_FUNC(GameScene);//自动释放对象


public:
	bool gameStart;
	bool firstStart;
	int balllastimpact;
	int balllast2brick;
	int gameover_f;
private:

	SimpleAudioEngine* audioengine;
	ParticleSystem* particle;
	CCMotionStreak* m_streak; //拖尾效果
	Ball* myBall;
	Baffle* myBaffle;
	Brick* myBricks[20];
	Brick* sampleBrick; //为获得转款长度
	//int baffley;
};