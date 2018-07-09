#include "StageSelectScene.h"
#include "GameClearScene.h"
#include "Const.h"
 
//using namespace cocos2d;の略。cocos2dの名前空間を利用
 
Scene *GameClear::createScene(){
     
    // 'scene' is an autorelease object
    auto scene = Scene::create();
     
    // 'layer' is an autorelease object
    auto layer = GameClear::create();
     
    // add layer as a child to scene
    scene->addChild(layer);
     
    // return the scene
    return scene;
 
     
}

bool GameClear::init()
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
	    auto lbl_title = LabelTTF::create("ゲームクリア", "HiraKakuProN-W6", 60);
	    lbl_title->setPosition(Point(origin.x + visibleSize.width/2,
	                                 origin.y + visibleSize.height
	                                 -lbl_title->getContentSize().height));
	    this->addChild(lbl_title, 1);

	    //スタートボタンを設置
	    auto startButton = MenuItemImage::create(
	                                           "images/start_button.png",  // 通常状態の画像
	                                           "images/start_button.png",  // 押下状態の画像
	                                           CC_CALLBACK_1(GameClear::pushStart, this)); // 押下時のアクション

	    startButton->setPosition(Point(visibleSize.width/2,
	                                 startButton->getContentSize().height/2 + 50));

    // create menu, it's an autorelease object
    auto menu = Menu::create(startButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    //スケジュールアップデートをスタート
    this->scheduleUpdate();

    return true;
}
 
void GameClear::pushStart(Ref* pSender)
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

//定期的に高速に呼ばれる関数
void GameClear::update(float delta)
 {
	srand((unsigned int)time(NULL)*frame);  //ランダムにパーティクルを生成
	int posX = (int)rand()% (int)VISIBLE_SIZE.width;
	int posY = (int)rand()% (int)VISIBLE_SIZE.height;
	int ran = rand()% 20;

	if(frame % (ran + 40) == 0){
		auto particle = ParticleSystemQuad::create("images/Fireworks.plist");
		particle->setPosition(Point(posX, posY));
		this->addChild(particle);
	}
	frame++;
}
