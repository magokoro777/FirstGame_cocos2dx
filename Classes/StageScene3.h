#ifndef __STAGE3_SCENE_H__
#define __STAGE3_SCENE_H__

#include "cocos2d.h"
#include "TowerSprite.h"
#include "UnitSprite.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "StageSelectScene.h"
USING_NS_CC;

class StageScene3 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    Size visibleSize;
    Size winSize;
    Sprite *bg;
    Vec2 origin;

    void createInitObjects();
    
    TowerSprite *territory;  //関数で使うから追加
    TowerSprite *territory2;

    UnitSprite *player;
    UnitSprite *player2;
    UnitSprite *player3;
    UnitSprite *enemy;

    Vector<UnitSprite*> playerVect;
    Vector<UnitSprite*> playerVect2;
    Vector<UnitSprite*> playerVect3;
    Vector<UnitSprite*> enemyVect;

    void addPlayer(Ref * sender);
    void addPlayer2(Ref * sender);
    void addPlayer3(Ref * sender);
    void addEnemy();
    void update(float delta);
    void collisionChecker();	//ユニット同士の衝突判定
    void collisionChecker2();	//ユニットと領地の衝突判定
    void calcDamage(UnitSprite *attacker, TowerSprite* target);
    void calcDamage2(UnitSprite *attacker, TowerSprite* target);

    void Pause(Ref* pSender);
    bool pause;
    void Menubtn(Ref* pSender);
    bool menu;
    int frame;

    void onTouchedMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent);

    // implement the "static create()" method manually
    CREATE_FUNC(StageScene3);
};

#endif // __STAGE3_SCENE_H__
