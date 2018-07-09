#include "StageSelectScene.h"
#include "HelloWorldScene.h"
#include "StageScene2.h"
#include "StageScene3.h"
#include "Const.h"
 
//using namespace cocos2d;の略。cocos2dの名前空間を利用
 
Scene *StageSelect::createScene(){
     
    // 'scene' is an autorelease object
    auto scene = Scene::create();
     
    // 'layer' is an autorelease object
    auto layer = StageSelect::create();
     
    // add layer as a child to scene
    scene->addChild(layer);
     
    // return the scene
    return scene;
 
     
}

bool StageSelect::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )           //initはゲームを初期化するときに使う関数。インスタンス＝ゲーム画面。
    {
        return false;
    }


    log("pass here");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	    //タイトルを設置
	    auto lbl_title = LabelTTF::create("ステージセレクト", "HiraKakuProN-W6", 60);
	    lbl_title->setPosition(Point(origin.x + visibleSize.width/2,
	                                 origin.y + visibleSize.height
	                                 -lbl_title->getContentSize().height));
	    this->addChild(lbl_title, 1);

	    //ステージ１ボタンを設置
	    auto stageButton = MenuItemImage::create(
	                                           "images/stage1.png",  // 通常状態の画像
	                                           "images/stage1.png",  // 押下状態の画像
	                                           CC_CALLBACK_1(StageSelect::pushStart, this)); // 押下時のアクション
	    stageButton->setPosition(Point(visibleSize.width*0.25,
	    			             VISIBLE_SIZE.height/2));

	    //ステージ２ボタンを設置
		auto stageButton2 = MenuItemImage::create(
											   "images/stage2.png",  // 通常状態の画像
											   "images/stage2.png",  // 押下状態の画像
											   CC_CALLBACK_1(StageSelect::pushStart2, this)); // 押下時のアクション
		stageButton2->setPosition(Point(visibleSize.width/2,
								 VISIBLE_SIZE.height/2));

		//ステージ３ボタンを設置
		auto stageButton3 = MenuItemImage::create(
											   "images/stage3.png",  // 通常状態の画像
											   "images/stage3.png",  // 押下状態の画像
											   CC_CALLBACK_1(StageSelect::pushStart3, this)); // 押下時のアクション
		stageButton3->setPosition(Point(visibleSize.width*0.75,
								 VISIBLE_SIZE.height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(stageButton, stageButton2, stageButton3, NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);

    return true;
}
 
void StageSelect::pushStart(Ref* pSender)
{
    // 遷移先の画面のインスタンス
    Scene *pScene = HelloWorld::createScene();
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
    Director::getInstance()->replaceScene(transition);
}

void StageSelect::pushStart2(Ref* pSender)
{
    // 遷移先の画面のインスタンス
    Scene *pScene = StageScene2::createScene();
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
    Director::getInstance()->replaceScene(transition);
}

void StageSelect::pushStart3(Ref* pSender)
{
    // 遷移先の画面のインスタンス
    Scene *pScene = StageScene3::createScene();
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
    Director::getInstance()->replaceScene(transition);
}
