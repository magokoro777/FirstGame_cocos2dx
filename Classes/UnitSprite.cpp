//
//  UnitSprite.cpp
//  FirstGame
//
//  Created by SonicNaoya on 2014/12/15.
//
//

#include "UnitSprite.h"

UnitSprite* UnitSprite::create(const std::string& filename)
{
    UnitSprite *sprite = new (std::nothrow) UnitSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
