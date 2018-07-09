#include "TitleScene.h"
#include "StageSelectScene.h"
 
//using namespace cocos2d;の略。cocos2dの名前空間を利用
 
Scene *Title::createScene(){
     
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Title::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
 
     
}

bool Title::init()
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

	 //背景を設置
	    Sprite* background = Sprite::create("images/start_image.png");
	    background->setPosition(Point(640/2, 1136/2));
	    background->setScale(2.5);
	    background->setRotation(90);
	    this->addChild(background, 0);


	    //タイトルを設置
	    auto lbl_title = LabelTTF::create("タワーディフェンス", "HiraKakuProN-W6", 30);
	    lbl_title->setPosition(Point(origin.x + visibleSize.width/2,
	                                 origin.y + visibleSize.height
	                                 -lbl_title->getContentSize().height));
	    this->addChild(lbl_title, 1);

	    //スタートボタンを設置
	    auto startButton = MenuItemImage::create(
	                                           "images/start_button.png",  // 通常状態の画像
	                                           "images/start_button.png",  // 押下状態の画像
	                                           CC_CALLBACK_1(Title::pushStart, this)); // 押下時のアクション

	    startButton->setPosition(Point(visibleSize.width/2,
	                                 startButton->getContentSize().height/2 + 50));

    // create menu, it's an autorelease object
    auto menu = Menu::create(startButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}
 
void Title::pushStart(Ref* pSender)
{
    // 遷移先の画面のインスタンス
    Scene *pScene = StageSelect::createScene();
     
    // 0.5秒かけてフェードアウトしながら次の画面に遷移します
    //    引数１:フィードの時間
    //    引数２：移動先のシーン
    //    引数３：フィードの色（オプション）
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
     
    //遷移実行  遷移時のアニメーション　http://study-cocos2d-x.info/scenelayer/55/
    Director::getInstance()->replaceScene(transition);
}

//void HelloWorld::menuCloseCallback(Ref* pSender)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}
