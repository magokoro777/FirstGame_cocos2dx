﻿#ifndef __FirstGame__TitleScene__
#define __FirstGame__TitleScene__
 
#include "cocos2d.h"
 
 USING_NS_CC;

class Title : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    //初期化のメソッド
    virtual bool init();
     
    //create()を使えるようにしている。
    CREATE_FUNC(Title);
    void pushStart(Ref* pSender); //スタートボタン押下時の処理宣言
};
 
 
#endif /* defined(__MyGameC__TitleScene__) */
