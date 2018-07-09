//
//  GameMenuLayer.cpp
//  FirstGame
//
//  Created by SonicNaoya on 2015/01/07.
//
//

#include "GameMenuLayer.h"
#include "Const.h"
#include "HelloWorldScene.h"

GameMenuLayer * GameMenuLayer::create()
{
    GameMenuLayer * ret = new GameMenuLayer();
    if (ret && ret->init())
    {
        ret->setup();
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void GameMenuLayer::setup()
{
	//HelloWorld *parent = HelloWorld::createScene();
	//parent->menu = true;
	setContentSize(VISIBLE_SIZE);
	setPosition(VISIBLE_SIZE/2);
	setTextureRect(this->getBoundingBox());
	setColor(Color3B::BLACK);
	setOpacity(100);

	//ゲームに戻るボタンを設置
		auto playBackButton = MenuItemImage::create("images/togame.png","images/togame.png",
												   CC_CALLBACK_1(GameMenuLayer::pushBack, this));
		playBackButton->setPosition(Point(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height*0.6));
		auto menu = Menu::create(playBackButton, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu);

	//あきらめるボタンを設置
		auto retireButton = MenuItemImage::create("images/retire.png","images/retire.png",
												   CC_CALLBACK_1(GameMenuLayer::pushRetire, this));
		retireButton->setPosition(Point(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height*0.4));
		auto menu2 = Menu::create(retireButton, NULL);
		menu2->setPosition(Vec2::ZERO);
		this->addChild(menu2);

	//タッチイベント
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(GameMenuLayer::onTouchBegan, this);
		listener->setSwallowTouches(true);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameMenuLayer::pushBack(Ref* pSender)
{
	Director::getInstance()->resume();
	((HelloWorld*)parentScene)->menu = false;

	this->removeFromParent();
}

void GameMenuLayer::pushRetire(Ref* pSender)
{
	Director::getInstance()->resume();
    Scene *pScene = StageSelect::createScene();
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
    Director::getInstance()->replaceScene(transition);
}

bool GameMenuLayer::onTouchBegan(Touch* touch, Event* event){
	log("pass here");

    //タッチをしたのレイヤーに貫通させないための処理
    auto rect = this -> getBoundingBox();
    if (!rect.containsPoint(touch -> getLocation())) {
        return false;
    }

    return true;
}
