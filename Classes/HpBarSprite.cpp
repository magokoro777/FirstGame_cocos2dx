//
//  HpBarSprite.cpp
//  FirstGame
//
//  Created by SonicNaoya on 2014/12/15.
//
//

#include "HpBarSprite.h"
#include "Const.h"

HpBarSprite* HpBarSprite::create()
{
    HpBarSprite *sprite = new (std::nothrow) HpBarSprite();
    if (sprite && sprite->init())
    {
    	sprite->setup();
        sprite->autorelease();
        return sprite;
    }
    else
    {
    	CC_SAFE_DELETE(sprite);
    }
    return nullptr;
}

void HpBarSprite::setup()
{
	  //HPバー表示
	    hpbar = Sprite::create("images/hpbar.png");
//	    hpbar->setAnchorPoint(Point::ZERO);
		hpbar->setScale(4.0);
		this->addChild(hpbar);

		hpframe = Sprite::create("images/hpbar_enemy.png");
//		hpframe->setAnchorPoint(Point::ZERO);
		hpframe->setScale(4.0);
		this->addChild(hpframe);
}


void HpBarSprite::calcHpBar(float newScale)
{
	hpbar->setScaleX(4.0 * newScale);
}

