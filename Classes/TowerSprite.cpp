//
//  TowerSprite.cpp
//  FirstGame
//
//  Created by SonicNaoya on 2014/12/15.
//
//

#include "TowerSprite.h"

TowerSprite* TowerSprite::create(const std::string& filename)
{
    TowerSprite *sprite = new (std::nothrow) TowerSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        sprite->setup();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void TowerSprite::setup(){
//	hpBar = HpBarSprite::create();
//	hpBar->setPosition(Point(this->getContentSize().width/2, 0));
//	this->addChild(hpBar);
}

void TowerSprite::setDefaultHp(float newHp){
	this->hp = newHp;
	this->maxHp = newHp;
	log("hp: %f", this->hp);
	log("maxHp: %f", this->maxHp);
}

void TowerSprite::setHp(float newHp)
{
	this->hp = newHp;
	log("this->hp:%f", this->hp);
	hpBar->calcHpBar(this->hp/this->maxHp);
	log("maxHp:%f", maxHp);
}

float TowerSprite::getHp()
{
	return this->hp;
}
