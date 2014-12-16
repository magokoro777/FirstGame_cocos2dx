#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "TowerSprite.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void createInitObjects();
    
    TowerSprite *territory;  //関数で使うから追加
    TowerSprite *territory2;

    Vector<Sprite*> playerVect;
    Vector<Sprite*> playerVect2;
    Vector<Sprite*> playerVect3;
    Vector<Sprite*> enemyVect;

    void addPlayer(Ref * sender);
    void addPlayer2(Ref * sender);
    void addPlayer3(Ref * sender);
    void addEnemy();
    void update(float delta);
    void collisionChecker();	//ユニット同士の衝突判定
    void collisionChecker2();	//ユニットと領地の衝突判定
    void calcDamage(Sprite *attacker, TowerSprite* target);
    int frame;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
