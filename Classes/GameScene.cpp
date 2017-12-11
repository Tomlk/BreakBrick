#include "GameScene.h"
int Brick::brickwidth = 0;
GameScene::GameScene()
{
	this->gameStart = false;
	this->firstStart = true;
	this->balllastimpact = 2; //1 上次碰撞上面 2 上次碰撞挡板 3 上次碰撞左边界 4上次碰撞右边界
	this->balllast2brick = 0;
	this->gameover_f = 0;
	audioengine = SimpleAudioEngine::getInstance();
	audioengine->preloadBackgroundMusic("sound/background2.wav");
	audioengine->preloadEffect("sound/normal_collide.wav");
	audioengine->preloadEffect("sound/brick_collide.wav");
	audioengine->preloadEffect("sound/died.wav");
	audioengine->playBackgroundMusic("sound/background2.wav", true);
}
GameScene::~GameScene()
{

}
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	//创建自动释放对象

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	return scene;
}
bool GameScene::init()
{
	//this->setTouchEnabled(true);//可以触摸
	auto visibleSize = Director::getInstance()->getVisibleSize(); //返回可视窗口大小
	if (!Layer::init())
	{
		return false;
	}

	Size mywinsize = Director::getInstance()->getWinSize();
	float winw = mywinsize.width; //获取屏幕宽度  
	float winh = mywinsize.height;//获取屏幕高度  
	//添加背景
	auto background_pic = Sprite::create("GameBackground.jpg");
	background_pic->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	float spx = background_pic->getTextureRect().getMaxX();
	float spy = background_pic->getTextureRect().getMaxY();
	background_pic->setScaleX(winw / spx); //设置精灵宽度缩放比例  
	background_pic->setScaleY(winh / spy);
	this->addChild(background_pic);

	
	//添加挡板
	myBaffle = Baffle::create("baffle.png");
	float spbx = myBaffle->getTextureRect().getMaxX();
	float spby = myBaffle->getTextureRect().getMaxY();
	myBaffle->setScaleX(winw / (spbx * 6)); //缩放倍数
	myBaffle->setScaleY(winh / (spby * 6));
	myBaffle->setHeight(spby*winh / (spby * 6));
	myBaffle->setLength(spbx*winw / (spbx * 6));
	myBaffle->setPosition(Vec2(visibleSize.width / 2, spby));
	this->addChild(myBaffle);
	

	int BallX = myBaffle->getPositionX();
	int BallY = myBaffle->getPositionY() + spby*winh / (spby * 12);
	
	myBaffle->setLength(spby*winh / (spby * 6));
	//baffley = myBaffle->getPositionY();



	//添加球
	myBall = Ball::create("Ball1.png");
	float spballx = myBall->getTextureRect().getMaxX();
	float spbally = myBall->getTextureRect().getMaxY();
	myBall->setScaleX(winw / (spballx * 24));
	myBall->setScaleY(winh / (spbally * 24));
	myBall->setPosition(Vec2(BallX, BallY));
	this->addChild(myBall);
	myBall->setBallradius(spbally*winh / (spbally * 48));

	//添加砖块
	blockplan1();

	//背景音乐，碰撞音效
	//BackgroundMusic();

	

	//添加球的拖尾效果
	m_streak = CCMotionStreak::create(2, 10, 20, Color3B::RED, "tuowei.png");
	//m_streak->setPosition(ccp(100, 110));
	this->addChild(m_streak, 1);
	CCActionInterval *colorAction = CCRepeatForever::create((CCActionInterval *)CCSequence::create(
		CCTintTo::create(0.2f, 255, 0, 0),
		CCTintTo::create(0.2f, 0, 255, 0),
		CCTintTo::create(0.2f, 0, 0, 255),
		CCTintTo::create(0.2f, 0, 255, 255),
		CCTintTo::create(0.2f, 255, 255, 0),
		CCTintTo::create(0.2f, 255, 0, 255),
		CCTintTo::create(0.2f, 255, 255, 255),
		NULL));
	m_streak->runAction(colorAction);

	//砖块碰撞粒子效果
	particle = ParticleFlower::create();
	particle->setTexture(TextureCache::sharedTextureCache()->addImage("explosition.png"));
	//this->setPosition(Vec2(winw, winh));
	this->addChild(particle);
	//监听事件
	auto listener = EventListenerTouchOneByOne::create();//单点触摸
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);//指针，回调
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	
	//注册监听事件
	auto disaptcher = Director::getInstance()->getEventDispatcher();
	listener->setSwallowTouches(true);
	disaptcher->addEventListenerWithSceneGraphPriority(listener, this);


	//定时器更新
	this->schedule(schedule_selector(GameScene::update));
	return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (!gameStart)
	{
		gameStart = true;
	}
	if (gameStart&&firstStart)
	{
		myBall->directionunitx = 0;
		myBall->directionunity = 1;

		//初始化操作皮球开始运动
		Size mywinsize = Director::getInstance()->getWinSize();
		float winw = mywinsize.width; //获取屏幕宽度  
		float winh = mywinsize.height;//获取屏幕高度  
		Point ballPoint(myBall->getPositionX(), myBall->getPositionY());
		Point tartgetpoint(myBall->getPositionX(), winh);
		//Point tartgetpoint = TargetPoint(myBall->directionunitx, myBall->directionunity = 1);
		double distance = sqrt(pow(ballPoint.x - tartgetpoint.x, 2) + pow(ballPoint.y - tartgetpoint.y, 2));
		//Point(myBall->getPositionX(),winh-myBall->getBallradius());
		CCMoveTo* move = CCMoveTo::create(distance / myBall->getMoveSpeed(), tartgetpoint);

		myBall->runAction(move);
		firstStart = false;
	}
	/*
	int Point2y = myBaffle->getPositiony();
	Point point2 = Point(-w, Point2y);
	int Bafflex = myBaffle->getPositionX();
	CCMoveBy* bafflemove = CCMoveBy::create(Bafflex / myBaffle->getMoveSpeed(), point2);
	myBaffle->runAction(bafflemove);
	*/
	return true;
}
void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	
	if (gameStart==1&&gameover_f==0)
	{
		//auto visibleSize = Director::getInstance()->getVisibleSize(); //返回可视窗口大小
		Size mywinsize = Director::getInstance()->getWinSize();
		float winw = mywinsize.width; //获取屏幕宽度  
		float winh = mywinsize.height;//获取屏幕高度  


		auto target = unused_event->getCurrentTarget();
		float base_width = mywinsize.width / 2;
		//float base_height = visibleSize.height / 5;
		Point point = touch->getLocation(); //已经是GL坐标

		myBaffle->setMoveDirection(point.x - base_width);
		int direction = myBaffle->getMoveDirection();
		//int direction=myBaffle->get

		//double unit_x = 50 * (point.x - base_width>0? 1:-1);
		int Point2y = myBaffle->getPositionY();
		//const int y = Point2y;
		if (direction > 0)
		{
			Point point2 = Point(winw, Point2y);
			int Bafflex = myBaffle->getPositionX();
			if (Bafflex < (winw - myBaffle->getLength() / 2))
			{
				CCMoveTo* bafflemove = CCMoveTo::create((winw - Bafflex) / myBaffle->getMoveSpeed(), point2);
				myBaffle->runAction(bafflemove);
			}
		}
		else
		{
			Point point2 = Point(0, Point2y);
			int Bafflex = myBaffle->getPositionX();
			if (Bafflex > myBaffle->getLength() / 2)
			{
				CCMoveTo* bafflemove = CCMoveTo::create(Bafflex / myBaffle->getMoveSpeed(), point2);
				myBaffle->runAction(bafflemove);
			}

		}


	}

}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	myBaffle->stopAllActions();
}

void GameScene::update(float dt)
{
	//拖尾跟随
	m_streak->setPosition(myBall->getPosition());


	//检测边界问题
	//挡板
	Size mywinsize = Director::getInstance()->getWinSize();
	float winh = mywinsize.height;
	float winw = mywinsize.width; //获取屏幕宽度 
	int bafflepointx = myBaffle->getPositionX();
	if (bafflepointx <= myBaffle->getLength() / 2 || bafflepointx >= (winw - myBaffle->getLength() / 2))
	{
		myBaffle->stopAllActions();
		//myBaffle->setPosition()
		if (bafflepointx <= myBaffle->getLength() / 2)
		{
			myBaffle->setPosition(myBaffle->getLength() / 2 + 10, myBaffle->getPositionY());
		}
		else if (bafflepointx >= (winw - myBaffle->getLength() / 2))
		{
			myBaffle->setPosition((winw - myBaffle->getLength() / 2) - 10, myBaffle->getPositionY());
		}
	}
	
	//小球和边界的碰撞

	
	if ((myBall->getPositionX() <= myBall->getBallradius())) //碰撞左边界
	{

		if (this->balllastimpact != 3)//左
		{
			myBall->directionunitx = -myBall->directionunitx;//取反
			Point ballPoint(myBall->getPositionX(), myBall->getPositionY());
			Point targetPoint = TargetPoint(myBall->directionunitx, myBall->directionunity);
			double distance = sqrt(pow(ballPoint.x - targetPoint.x, 2) + pow(ballPoint.y - targetPoint.y, 2));
			//myBall->stopAllActions(); //先停止其它动作？
			CCMoveTo* moveto = CCMoveTo::create(distance / myBall->getMoveSpeed(), targetPoint);
			myBall->runAction(moveto);
			this->balllastimpact = 3;
			this->balllast2brick = 0;
			audioengine->playEffect("sound/normal_collide.wav");
		}
	}

	else if ((winw - myBall->getPositionX() <= myBall->getBallradius())) //碰撞右边界
	{

		if (this->balllastimpact != 4)//右
		{
			myBall->directionunitx = -myBall->directionunitx;//取反
			Point ballPoint(myBall->getPositionX(), myBall->getPositionY());
			Point targetPoint = TargetPoint(myBall->directionunitx, myBall->directionunity);
			double distance = sqrt(pow(ballPoint.x - targetPoint.x, 2) + pow(ballPoint.y - targetPoint.y, 2));
			//myBall->stopAllActions(); //先停止其它动作？
			CCMoveTo* moveto = CCMoveTo::create(distance / myBall->getMoveSpeed(), targetPoint);
			myBall->runAction(moveto);
			this->balllastimpact = 4;
			this->balllast2brick = 0;
			audioengine->playEffect("sound/normal_collide.wav");


		}
	}
	else if (winh - myBall->getPositionY() <= myBall->getBallradius())  //碰撞上边界
	{

		if (this->balllastimpact != 1)
		{
			myBall->stopAllActions(); //防止action的叠加****!!!
			myBall->directionunity = -myBall->directionunity;//取反
			Point ballPoint(myBall->getPositionX(), myBall->getPositionY());
			//Point targetPoint(myBall->getPositionX(), myBaffle->getPositionY());
			Point targetPoint = TargetPoint(myBall->directionunitx, myBall->directionunity);
			//myBall->directionunity = -myBall->directionunity;//取反
			double distance = sqrt(pow(ballPoint.x - targetPoint.x, 2) + pow(ballPoint.y - targetPoint.y, 2));
			//myBall->stopAllActions(); //先停止其它动作？
			CCMoveTo* moveto = CCMoveTo::create(distance / myBall->getMoveSpeed(), targetPoint);
			myBall->runAction(moveto);
			this->balllastimpact = 1;
			this->balllast2brick = 0;
			audioengine->playEffect("sound/normal_collide.wav");
		}

	}
	else if (myBall->getPositionY() <= myBaffle->getHeight() / 2) //掉落
	{
		if (gameover_f == 0)
		{
			
			audioengine->playEffect("sound/died.wav");
			audioengine->stopBackgroundMusic();
			gameover_f = 1;
		}
		myBall->stopAllActions();
		//audioengine->playEffect("sound/normal_collide.wav");
	}


	//小球和挡板的碰撞
	if (gameStart)
	{
		if (myBall->getPositionY() < 1.1*myBaffle->getHeight()) //
		{
			int X_distance = myBall->getPositionX() - myBaffle->getPositionX();
			if (abs(X_distance)
				< myBaffle->getLength()*0.5) //碰撞
			{
				if (this->balllastimpact != 2)
				{
					myBall->stopAllActions();//防止action的叠加****!!!
					double X_coefficient = X_distance / (myBaffle->getLength()*0.5);
					if (X_coefficient > 1) X_coefficient = 1;
					else if (X_coefficient < -1) X_coefficient = -1;
					myBall->directionunitx = X_coefficient;
					myBall->directionunity = sqrt(1 - pow(X_coefficient, 2)); //经挡板后y方向一定为正
					CCLOG("directionunitx:%lf  directionunity %lf \n", myBall->directionunitx, myBall->directionunity);
					//Point targetPoint(myBall->getPositionX(), winh);
					Point targetPoint = TargetPoint(myBall->directionunitx, myBall->directionunity);
					//CCLOG("TargetPoint.x:%d  TargetPoint.y %d \n", targetPoint.x, targetPoint.y);
					Point ballPoint(myBall->getPositionX(), myBall->getPositionY());
					//CCLOG("ballPoint.x:%d  myBall->getPositionx %d \n", ballPoint.x, myBall->getPositionX());
					double distance = sqrt(pow(ballPoint.x - targetPoint.x, 2) + pow(ballPoint.y - targetPoint.y, 2));

					//myBall->stopAllActions(); //先停止其它动作？
					CCMoveTo* moveto = CCMoveTo::create(distance / myBall->getMoveSpeed(), targetPoint);
					myBall->runAction(moveto);
					this->balllastimpact = 2;
					this->balllast2brick = 0;
					audioengine->playEffect("sound/normal_collide.wav");
				}
			}

		}
	}

	
	//小球和砖块的碰撞先判断砖块上下面的碰撞，在判断左右面的碰撞优先级：上下面>左右面
	int LorRlength = Brick::brickwidth*0.5 + myBall->getBallradius();
	int TorBlength = Brick::brickwidth*0.25 + myBall->getBallradius();
	for (int i = 0; i < 20; i++)
	{
		if (myBricks[i]->isExit())  //存在才需要判断
		{
			if (abs(myBricks[i]->getPositionY() - myBall->getPositionY()) < TorBlength) //上下面可能碰撞
			{
				if (abs(myBricks[i]->getPositionX() - myBall->getPositionX()) < Brick::brickwidth*0.5) // 与i砖块上下面确定碰撞
				{

					//	CCLOG("ball run into a brick\n");
					if (this->balllast2brick != i + 1)
					{
						this->balllastimpact = 0; //代表上次碰撞是砖块
						myBall->stopAllActions();//防止action的叠加****!!!
						CCLOG("ball run into a brick\n");
						myBall->directionunity = -myBall->directionunity;//取反
						Point ballPoint(myBall->getPositionX(), myBall->getPositionY());
						//Point targetPoint(myBall->getPositionX(), myBaffle->getPositionY());
						//Point targetPoint(myBaffle->getPositionX(), myBaffle->getPositionY());
						Point targetPoint = TargetPoint(myBall->directionunitx, myBall->directionunity);
						CCLOG("TargetPoint.x:%d  TargetPoint.y %d \n", targetPoint.x, targetPoint.y);
						//myBall->directionunity = -myBall->directionunity;//取反
						double distance = sqrt(pow(ballPoint.x - targetPoint.x, 2) + pow(ballPoint.y - targetPoint.y, 2));
						//myBall->stopAllActions(); //先停止其它动作？
						CCMoveTo* moveto = CCMoveTo::create(distance / myBall->getMoveSpeed(), targetPoint);

						myBall->runAction(moveto);
						this->balllast2brick = i + 1;
						myBricks[i]->addAttackedTime();
						CCLOG("被击中，当前被击中次数%d\n", myBricks[i]->getAttackedTime());
						if (myBricks[i]->getAttackedTime() >=myBricks[i]->getBrickType())  myBricks[i]->setBrickExitFlag(0);
						else
						{
							myBricks[i]->setTexture(myBricks[i - 4*myBricks[i]->getAttackedTime()]->getTexture());
						}
						if (!myBricks[i]->isExit())  //已经消失
						{
							particle->setPosition(myBricks[i]->getPosition());
							myBricks[i]->setVisible(false);

						}

						audioengine->playEffect("sound/brick_collide.wav");
					}
					break;

				}

			}
			else if (abs(myBricks[i]->getPositionX() - myBall->getPositionX()) < LorRlength) //左右面可能碰撞
			{
				if (abs(myBricks[i]->getPositionY() - myBall->getPositionY()) < Brick::brickwidth*0.25) // 与i砖块左右面确定碰撞
				{

					//	CCLOG("ball run into a brick\n");
					if (this->balllast2brick != i + 1)
					{
						this->balllastimpact = 0; //代表上次碰撞是砖块
						myBall->stopAllActions();//防止action的叠加****!!!
						CCLOG("ball run into a brick\n");
						myBall->directionunitx = -myBall->directionunitx;//取反
						Point ballPoint(myBall->getPositionX(), myBall->getPositionY());
						//Point targetPoint(myBall->getPositionX(), myBaffle->getPositionY());
						//Point targetPoint(myBaffle->getPositionX(), myBaffle->getPositionY());
						Point targetPoint = TargetPoint(myBall->directionunitx, myBall->directionunity);
						CCLOG("TargetPoint.x:%d  TargetPoint.y %d \n", targetPoint.x, targetPoint.y);
						//myBall->directionunity = -myBall->directionunity;//取反
						double distance = sqrt(pow(ballPoint.x - targetPoint.x, 2) + pow(ballPoint.y - targetPoint.y, 2));
						//myBall->stopAllActions(); //先停止其它动作？
						CCMoveTo* moveto = CCMoveTo::create(distance / myBall->getMoveSpeed(), targetPoint);

						myBall->runAction(moveto);
						this->balllast2brick = i + 1;
						myBricks[i]->addAttackedTime();
						if (myBricks[i]->getAttackedTime() >= myBricks[i]->getBrickType())  myBricks[i]->setBrickExitFlag(0);
						else
						{
							myBricks[i]->setTexture(myBricks[i - 4 * myBricks[i]->getAttackedTime()]->getTexture());
						}
						if (!myBricks[i]->isExit())  //已经消失
						{
							particle->setPosition(myBricks[i]->getPosition());
							myBricks[i]->setVisible(false);

						}
						audioengine->playEffect("sound/brick_collide.wav");

					}
					break;


				}
			}
		
		}
		//else if ()
	//	break; //跳出for循环
	}
	


}
Point GameScene::TargetPoint(double directionx, double directiony)
{
	Size mywinsize = Director::getInstance()->getWinSize();
	double winw = mywinsize.width; //获取屏幕宽度 
	double winh = mywinsize.height; //获取屏幕高度

	if (directionx > 0)
	{
		if (directiony > 0)
		{
			double ball2right = winw - myBall->getPositionX();
			double ball2top = winh - myBall->getPositionY();
			if (ball2top*directionx / directiony < ball2right)
			{

				Point point(myBall->getPositionX() + ball2top*directionx / directiony, winh);
			//	CCLOG("TargetPoint.x:%d  TargetPoint.y %d \n", point.x, point.y);
			//	CCLOG("TargetPoint.x:%d  TargetPoint.y %d \n", point.x, point.y);
				return point;
			}
			else
			{
				Point point(winw, myBall->getPositionY() + ball2right*directiony / directionx);
				return point;
			}

		}
		else if (directiony < 0)
		{
			double ball2right = winw - myBall->getPositionX();
			double ball2bottem = myBall->getPositionY();
			if (ball2bottem*directionx / (-directiony) < ball2right)
			{
				Point point(myBall->getPositionX() + ball2bottem*directionx / (-directiony), 0);
				return point;
			}
			else
			{
				Point point(winw, myBall->getPositionY() - ball2right*(-directiony) / directionx);
				return point;
			}

		}

	}
	else if (directionx < 0)
	{

		if (directiony > 0)
		{
			double ball2left = myBall->getPositionX();
			double ball2top = winh - myBall->getPositionY();
			if (ball2top*(-directionx) / directiony < ball2left)
			{
				Point point(myBall->getPositionX() - ball2top*(-directionx) / directiony, winh);
				return point;
			}
			else
			{
				Point point(0, myBall->getPositionY() + ball2left*directiony / (-directionx));
				return point;
			}

		}
		else if (directiony < 0)
		{
			double ball2left = myBall->getPositionX();
			double ball2bottem = myBall->getPositionY();
			if (ball2bottem*(-directionx) / (-directiony) < ball2left)
			{
				Point point(myBall->getPositionX() - ball2bottem*(-directionx) / (-directiony), 0);
				return point;
			}
			else
			{
				Point point(0, myBall->getPositionY() - ball2left*(-directiony) / (-directionx));
				return point;
			}

		}
	}
	else//if (directionx == 0)
	{
		if (directiony > 0)
		{
			Point point(myBall->getPositionX(), winh);
			return point;
		}
		else{
			Point point(myBall->getPositionX(), 0);
			return point;
		}
	}


}
void GameScene::blockplan1()
{
	
	Size mywinsize = Director::getInstance()->getWinSize();
	double winw = mywinsize.width; //获取屏幕宽度 
	double winh = mywinsize.height; //获取屏幕高度


	sampleBrick = Brick::create("brick1.png", 1);
	float spballx = sampleBrick->getTextureRect().getMaxX();
	float spbally = sampleBrick->getTextureRect().getMaxY();
	sampleBrick->setScaleX(winw / (spballx * 12));
	sampleBrick->setScaleY(winh / (spbally * 12));
	Brick::brickwidth = spballx*winw / (spballx * 12);
	//sampleBrick->setBrickWidth(spballx*winw / (spballx * 12));

	double firstbricksH = 0.9*winh;
	double firstbricksW = winw/12;
	double secondbricksW = winw / 12 * 7;

	double secondbricksH = 0.7*winh;

	double thirdbricksH = 0.5*winh;

	double thirdbricksW = winw / 3;
	for (int i = 0; i < 4; i++)
	{

		myBricks[i] = Brick::create("brick1.png",1);
		myBricks[i]->setScaleX(winw / (spballx * 12));
		myBricks[i]->setScaleY(winh / (spbally * 12));
		myBricks[i]->setPosition(Vec2(firstbricksW+(i + 0.5)*Brick::brickwidth, firstbricksH));
		//CCLOG("firstbricksW:%fl", firstbricksW);
		this->addChild(myBricks[i]);

	}

	for (int i = 4; i < 8; i++)
	{

		myBricks[i] = Brick::create("brick2.png", 2);
		myBricks[i]->setScaleX(winw / (spballx * 12));
		myBricks[i]->setScaleY(winh / (spbally * 12));
		myBricks[i]->setPosition(Vec2(secondbricksW + (i-4 + 0.5)*Brick::brickwidth, firstbricksH));
		//CCLOG("firstbricksW:%fl", firstbricksW);
		this->addChild(myBricks[i]);

	}

	for (int i = 8; i < 12; i++)
	{

		myBricks[i] = Brick::create("brick3.png", 3);
		myBricks[i]->setScaleX(winw / (spballx * 12));
		myBricks[i]->setScaleY(winh / (spbally * 12));
		myBricks[i]->setPosition(Vec2(firstbricksW + (i-8 + 0.5)*Brick::brickwidth, secondbricksH));
		//CCLOG("firstbricksW:%fl", firstbricksW);
		this->addChild(myBricks[i]);

	}

	for (int i = 12; i < 16; i++)
	{

		myBricks[i] = Brick::create("brick4.png", 4);
		myBricks[i]->setScaleX(winw / (spballx * 12));
		myBricks[i]->setScaleY(winh / (spbally * 12));
		myBricks[i]->setPosition(Vec2(secondbricksW + (i-12 + 0.5)*Brick::brickwidth, secondbricksH));
		//CCLOG("firstbricksW:%fl", firstbricksW);
		this->addChild(myBricks[i]);

	}

	for (int i = 16; i < 20; i++)
	{

		myBricks[i] = Brick::create("brick5.png", 5);
		myBricks[i]->setScaleX(winw / (spballx * 12));
		myBricks[i]->setScaleY(winh / (spbally * 12));
		myBricks[i]->setPosition(Vec2(thirdbricksW + (i-16 + 0.5)*Brick::brickwidth, thirdbricksH));
		//CCLOG("firstbricksW:%fl", firstbricksW);
		this->addChild(myBricks[i]);

	}




}

//http://sc.chinaz.com/yinxiao/171026288681.htm#down
//https://www.cnblogs.com/HangZhe/p/5812543.html