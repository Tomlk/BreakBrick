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
	virtual bool init();//��ʼ��
	//���ש���ʼ������
	void blockplan1();


	//��������
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	static Scene* createScene();
	//��ʱ��
	virtual void update(float);

	Point TargetPoint( double directionx, double directiony);

	CREATE_FUNC(GameScene);//�Զ��ͷŶ���


public:
	bool gameStart;
	bool firstStart;
	int balllastimpact;
	int balllast2brick;
	int gameover_f;
private:

	SimpleAudioEngine* audioengine;
	ParticleSystem* particle;
	CCMotionStreak* m_streak; //��βЧ��
	Ball* myBall;
	Baffle* myBaffle;
	Brick* myBricks[20];
	Brick* sampleBrick; //Ϊ���ת���
	//int baffley;
};