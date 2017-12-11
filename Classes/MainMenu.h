#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class MainMenu:public Layer
{
public:
	MainMenu();
	~MainMenu();
	static Scene* createScene();
	void InitMenu(float, float);
	void StartSwitchCallback(CCObject* object);
	void QuitSwitchCallback(CCObject* object);
	virtual bool init();
	CREATE_FUNC(MainMenu); //±ØÐëÎªcreateScene
private:
	CCMenu* menu;
};

