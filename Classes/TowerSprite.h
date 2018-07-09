//
//  TowerSprite.h
//  FirstGame
//
//  Created by SonicNaoya on 2014/12/15.
//
//

#ifndef __FirstGame__TowerSprite__
#define __FirstGame__TowerSprite__

#include <stdio.h>
#include "cocos2d.h"
#include "HpBarSprite.h"


USING_NS_CC;

class TowerSprite : public Sprite
{

    CC_SYNTHESIZE(HpBarSprite*, hpBar, HpBar);

public:
    static TowerSprite* create(const std::string& filename);
    void setup();
    //setter
    void setDefaultHp(float newHp);
    void setHp(float newHp);
    float getHp();


private:
    float hp;
    float maxHp;
    
};

#endif /* defined(__FirstGame__TowerSprite__) */
