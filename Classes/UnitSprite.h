//
//  TowerSprite.h
//  FirstGame
//
//  Created by SonicNaoya on 2014/12/15.
//
//

#ifndef __FirstGame__UnitSprite__
#define __FirstGame__UnitSprite__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class UnitSprite : public Sprite
{

    CC_SYNTHESIZE(int, attack, Attack);
    
public:
    static UnitSprite* create(const std::string& filename);

//    //setter
//    void setHp(int newHp);
//    int getHp();
//    
//private:
//    int hp;
    
};

#endif /* defined(__FirstGame__TowerSprite__) */