#ifndef __FirstGame__HpBarSprite__
#define __FirstGame__HpBarSprite__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class HpBarSprite : public Sprite
{

    //CC_SYNTHESIZE(int, parentHp, ParentHp);
    //CC_SYNTHESIZE(Ref*, parentHp, ParentHp);
    
public:
    static HpBarSprite* create();

    void setup();
    void calcHpBar(float newScale);

	Sprite *hpbar;
	Sprite *hpframe;


private:
    
};

#endif /* defined(__FirstGame__HpBarSprite__) */
