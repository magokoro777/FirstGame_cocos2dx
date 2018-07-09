//
//  GameMenuLayer.h
//  FirstGame
//
//  Created by SonicNaoya on 2015/01/07.
//
//

#ifndef __FirstGame__GameMenuLayer__
#define __FirstGame__GameMenuLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class GameMenuLayer : public Sprite
{
	CC_SYNTHESIZE(Ref*, parentScene, ParentScene);

public:
    static GameMenuLayer * create();
    
    void setup();
    void pushBack(Ref* pSender);
    void pushRetire(Ref* pSender);
    bool onTouchBegan(Touch* touch, Event* event);
};

#endif /* defined(__FirstGame__GameMenuLayer__) */
