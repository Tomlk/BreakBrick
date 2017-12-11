#include "MainMenu.h"
USING_NS_CC;//using namespace cocos2d;

MainMenu::MainMenu()
{
}
Scene* MainMenu:: createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}
MainMenu::~MainMenu()
{
}

bool MainMenu::init()
{
	if (!Layer::init())//��ʼ��������
	{
		return false;
	}

	Size  VisibleSize = Director::getInstance()->getVisibleSize();
	InitMenu(VisibleSize.width / 2, VisibleSize.height / 2);
	auto background = Sprite::create("MenuBackground.jpg");
	background->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 2));
	this->addChild(background,0); //��ײ�
}
void MainMenu::InitMenu(float x, float y )
{
	CCMenuItemImage* Start = CCMenuItemImage::create(
		"menu_start.jpg", "menu_start.jpg", this, menu_selector(MainMenu::StartSwitchCallback));
	Start->setPosition(Director::getInstance()->convertToGL(Point(250, 600)));

	CCMenuItemImage* Quit = CCMenuItemImage::create(
		"menu_quit.jpg", "menu_quit.jpg", this, menu_selector(MainMenu::QuitSwitchCallback));
	Quit->setPosition(Director::getInstance()->convertToGL(Point(250, 800)));

	menu = CCMenu::create(Start, Quit, NULL);
	menu->setPosition(ccp(x, y));
	this->addChild(menu, 1); //������
}
void MainMenu::StartSwitchCallback(CCObject* object)
{
	//CCDirector::sharedDirector()->replaceScene(GameScene::createScene());  //GameSceneΪ��Ϸ����
}
void MainMenu::QuitSwitchCallback(CCObject* object)
{
	Director::getInstance()->end();
}


