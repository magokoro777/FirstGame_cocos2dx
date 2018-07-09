#ifndef __FirstGame__StageSelectScene__
#define __FirstGame__StageSelectScene__
 
#include "cocos2d.h"
 
 USING_NS_CC;

class StageSelect : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    //初期化のメソッド
    virtual bool init();
     
    //create()を使えるようにしている。
    CREATE_FUNC(StageSelect);
    void pushStart(Ref* pSender); //ステージ１ボタン押下時の処理宣言
    void pushStart2(Ref* pSender); //ステージ２ボタン押下時の処理宣言
    void pushStart3(Ref* pSender); //ステージ３ボタン押下時の処理宣言
};
 
 
#endif /* defined(__MyGameC__TitleScene__) */
