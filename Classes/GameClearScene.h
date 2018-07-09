#ifndef __FirstGame__GameClearScene__
#define __FirstGame__GameClearScene__
 
#include "cocos2d.h"
 
 USING_NS_CC;

class GameClear : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    //初期化のメソッド
    virtual bool init();

    void update(float delta);
    int frame;
//    ParticleSystemQuad* particle;
    //create()を使えるようにしている。
    CREATE_FUNC(GameClear);
    void pushStart(Ref* pSender); //スタートボタン押下時の処理宣言
};
 
 
#endif /* defined(__MyGameC__TitleScene__) */
