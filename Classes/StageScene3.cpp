#include "StageScene3.h"
#include "TowerSprite.h"
#include "UnitSprite.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "StageSelectScene.h"
#include "GameMenuLayer.h"
#include "Const.h"

#include <extensions/cocos-ext.h>
USING_NS_CC_EXT;
Scene* StageScene3::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageScene3::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool StageScene3::init()
{
    // 1. super init first
    if ( !Layer::init() )           //initはゲームを初期化するときに使う関数。インスタンス＝ゲーム画面。
    {
        return false;
    }
    
    visibleSize = VISIBLE_SIZE;
    origin = Director::getInstance()->getVisibleOrigin();

    createInitObjects();

    //ボタンの生成（画像）
     //画面サイズの取得
     winSize = Director::getInstance()->getWinSize();
     auto pBtnItem1 = MenuItemImage::create("images/btn1.png","images/btn1.png", CC_CALLBACK_1(StageScene3::addPlayer, this));
     auto pBtnItem2 = MenuItemImage::create("images/btn2.png","images/btn2.png", CC_CALLBACK_1(StageScene3::addPlayer2, this));
     auto pBtnItem3 = MenuItemImage::create("images/btn3.png","images/btn3.png", CC_CALLBACK_1(StageScene3::addPlayer3, this));
     pBtnItem1 -> setPosition(Point(-pBtnItem1->getContentSize().width*2,pBtnItem1->getContentSize().height));
     pBtnItem2 -> setPosition(Point(0,pBtnItem2->getContentSize().height));
     pBtnItem3 -> setPosition(Point(pBtnItem3->getContentSize().width*2,pBtnItem3->getContentSize().height));
     pBtnItem1 -> setScale(2.0);
     pBtnItem2 -> setScale(2.0);
     pBtnItem3 -> setScale(2.0);
     Menu *pMenu = Menu::create(pBtnItem1,pBtnItem2,pBtnItem3, NULL);
     pMenu->setPosition(Point(winSize.width/2,0));
     this->addChild(pMenu);

     //一時停止ボタン
     auto pauseButton = MenuItemImage::create("images/pause.png","images/pause.png", CC_CALLBACK_1(StageScene3::Pause, this));
     pauseButton -> setPosition(Point(VISIBLE_SIZE.width-pauseButton->getContentSize().width/4,pauseButton->getContentSize().height/4));
     pauseButton -> setScale(0.4);
     pause = false;
     auto pauseMenu = Menu::create(pauseButton, NULL);
     pauseMenu->setPosition(Vec2::ZERO);
     this->addChild(pauseMenu);

     //メニューボタン
     auto menuButton = MenuItemImage::create("images/menu.png","images/menu.png", CC_CALLBACK_1(StageScene3::Menubtn, this));
     menuButton -> setPosition(Point(VISIBLE_SIZE.width-menuButton->getContentSize().width/2,pauseButton->getContentSize().height/4));
	 menuButton -> setScale(0.4);
	 menu = false;
	 auto menuMenu = Menu::create(menuButton, NULL);
	 menuMenu->setPosition(Vec2::ZERO);
	 this->addChild(menuMenu);

    //スケジュールアップデートをスタート
    this->scheduleUpdate();

    return true;
}


//定期的に高速に呼ばれる関数
void StageScene3::update(float delta)
 {
    log("update");
    srand((unsigned int)time(NULL)*frame);  //ランダムに敵を生成
    int mix=rand()% 160 + 40;

    if(territory2->isVisible() == true){
    	if(frame % mix == 0){
    		addEnemy();
    	}
    	collisionChecker();
		collisionChecker2();
    }
    frame++;
}

void StageScene3::createInitObjects()
{
	auto listener = EventListenerTouchAllAtOnce::create();
	    listener->onTouchesMoved = CC_CALLBACK_2(StageScene3::onTouchedMoved, this);
	    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto mainView = ScrollView::create(VISIBLE_SIZE);
	 	 mainView->setDirection(ScrollView::Direction::HORIZONTAL);
		 mainView->setBounceable(false);
		 mainView->setPosition(Point::ZERO);
		 this->addChild(mainView);

	//ゲーム背景の追加
	    bg = Sprite::create("images/bg.png");
	    bg->setScale(2.5);

	    mainView->setContainer(bg);
	    mainView->setContentSize(Size(bg->getContentSize()));

	//プレイヤー領地の追加
	    territory = TowerSprite::create("images/player1_1.png");
	    territory->setPosition(Point(territory->getContentSize().width, bg->getContentSize().height/4));
	    territory->setScale(0.5);
	    territory->setRotation(90);
	    territory->setHp(100);
	    bg->addChild(territory,50,50);

	    //log("HPは:%d",territory->getHp());

	 //エネミー領地の追加
	    territory2 = TowerSprite::create("images/enemy1_1.png");
	    territory2->setPosition(Point(bg->getContentSize().width-territory2->getContentSize().width, bg->getContentSize().height/4));
	    territory2->setScale(0.5);
	    territory2->setRotationX(-90);
	    territory2->setHp(100);
	    bg->addChild(territory2,50,50);

	  //HPバー表示
	    auto hpbar = Sprite::create("images/hpbar.png");
		hpbar->setPosition(Point(VISIBLE_SIZE.width*0.2, VISIBLE_SIZE.height - hpbar->getContentSize().height*1.2));
		hpbar->setScaleX(2.5);
		this->addChild(hpbar);

		auto hpframe = Sprite::create("images/hpbar_enemy.png");
		hpframe->setPosition(hpbar->getPosition());
		hpframe->setScale(4.0);
		this->addChild(hpframe);
}

void StageScene3::addPlayer(Ref * sender)
{
	//プレイヤーの追加
	    player = UnitSprite::create("images/missile2.png");
	    player->setPosition(territory->getPosition());
	    player->setAttack(10);
	    if(pause == false)
	    bg->addChild(player);

	    playerVect.pushBack(player);

	    auto move = MoveTo::create(5.0f, territory2->getPosition());
	    /*auto callfunc = CallFunc::create([=](){
	    	player->removeFromParent();
	    	playerVect.eraseObject(player);
	    });
	    auto seq = Sequence::create(move, callfunc, NULL);*/
	    player->runAction(move);
}

void StageScene3::addPlayer2(Ref * sender)
{
	//プレイヤーの追加
	    player2 = UnitSprite::create("images/missile3.png");
	    player2->setPosition(territory->getPosition());
	    player2->setAttack(10);
	    if(pause == false)
	    bg->addChild(player2);

	    playerVect2.pushBack(player2);

	    auto move = MoveTo::create(5.0f, territory2->getPosition());
	    /*auto callfunc = CallFunc::create([=](){
	    	player->removeFromParent();
	    	playerVect2.eraseObject(player);
	    });
	    auto seq = Sequence::create(move, callfunc, NULL);*/
	    player2->runAction(move);
}

void StageScene3::addPlayer3(Ref * sender)
{
	//プレイヤーの追加
	    player3 = UnitSprite::create("images/missile4.png");
	    player3->setPosition(territory->getPosition());
	    player3->setAttack(10);
	    if(pause == false)
	    bg->addChild(player3);

	    playerVect3.pushBack(player3);

	    auto move = MoveTo::create(5.0f, territory2->getPosition());
	    /*auto callfunc = CallFunc::create([=](){
	    	player->removeFromParent();
	    	playerVect3.eraseObject(player);
	    });
	    auto seq = Sequence::create(move, callfunc, NULL);*/
	    player3->runAction(move);
}

void StageScene3::addEnemy()
{
	//エネミーの追加
		    enemy = UnitSprite::create("images/missile1.png");
		    enemy->setPosition(territory2->getPosition());
		    enemy->setAttack(10);
		    bg->addChild(enemy);

		    enemyVect.pushBack(enemy);

		    auto move = MoveTo::create(5.0f, territory->getPosition());
		    enemy->runAction(move);
}

void StageScene3::collisionChecker()		//ユニット同士の衝突判定
{
	//プレイヤーの敵との衝突判定
	for(UnitSprite * playerArray : playerVect){
		for(UnitSprite * enemyArray : enemyVect){
			if(playerArray->getBoundingBox().intersectsRect(enemyArray->getBoundingBox())){
				//player->attackForTarget(enemy);		//別クラスの呼び出し方
				enemyArray->removeFromParent();		//敵を画面から除去
				enemyVect.eraseObject(enemyArray);	//敵を配列から除去

				break;
			}
		}
	}
	//プレイヤーの敵との衝突判定
	for(UnitSprite * playerArray2 : playerVect2){
		for(UnitSprite * enemyArray : enemyVect){
			if(playerArray2->getBoundingBox().intersectsRect(enemyArray->getBoundingBox())){
				//player->attackForTarget(enemy);		//別クラスの呼び出し方
				enemyArray->removeFromParent();		//敵を画面から除去
				enemyVect.eraseObject(enemyArray);	//敵を配列から除去

				break;
			}
		}
	}
	//プレイヤーの敵との衝突判定
	for(UnitSprite * playerArray3 : playerVect3){
		for(UnitSprite * enemyArray : enemyVect){
			if(playerArray3->getBoundingBox().intersectsRect(enemyArray->getBoundingBox())){
				//player->attackForTarget(enemy);		//別クラスの呼び出し方
				enemyArray->removeFromParent();		//敵を画面から除去
				enemyVect.eraseObject(enemyArray);	//敵を配列から除去

				break;
			}
		}
	}
}

void StageScene3::collisionChecker2()		//ユニットと領地の衝突判定
{
	//プレイヤーユニットと敵領地の衝突判定
	for(UnitSprite * playerArray : playerVect){
		if(playerArray->getBoundingBox().intersectsRect(territory2->getBoundingBox())){
			calcDamage(playerArray, territory2);
			playerArray->removeFromParent();		//プレイヤーを画面から除去
			playerVect.eraseObject(playerArray);	//プレイヤーを配列から除去

			break;
		}
	}
	//プレイヤーユニットと敵領地の衝突判定
	for(UnitSprite * playerArray2 : playerVect2){
		if(playerArray2->getBoundingBox().intersectsRect(territory2->getBoundingBox())){
			calcDamage(playerArray2, territory2);
			playerArray2->removeFromParent();		//プレイヤーを画面から除去
			playerVect2.eraseObject(playerArray2);	//プレイヤーを配列から除去

			break;
		}
	}
	//プレイヤーユニットと敵領地の衝突判定
	for(UnitSprite * playerArray3 : playerVect3){
		if(playerArray3->getBoundingBox().intersectsRect(territory2->getBoundingBox())){
			calcDamage(playerArray3, territory2);
			playerArray3->removeFromParent();		//プレイヤーを画面から除去
			playerVect3.eraseObject(playerArray3);	//プレイヤーを配列から除去

			break;
		}
	}
	//敵ユニットとプレイヤー領地の衝突判定
	for(UnitSprite * enemyArray : enemyVect){
		if(enemyArray->getBoundingBox().intersectsRect(territory->getBoundingBox())){
			calcDamage2(enemyArray, territory);
			enemyArray->removeFromParent();		//敵を画面から除去
			enemyVect.eraseObject(enemyArray);	//敵を配列から除去

			break;
		}
	}
}

void StageScene3::calcDamage(UnitSprite *attacker, TowerSprite* target)	//プレイヤーユニットと敵領地
{
			//サウンド再生
			//パーティクルを出す
			target->setHp(target->getHp() - attacker->getAttack());
			if(target->getHp() <= 0){
				auto delay = DelayTime::create(3.0);
				auto callfunc = CallFunc::create([this](){
				//画面移動
					Scene *pScene = GameClear::createScene();
					TransitionFade* transition = TransitionFade::create(1.0f, pScene);
					Director::getInstance()->replaceScene(transition);
				});
				auto seq = Sequence::create(delay, callfunc, NULL);
				this->runAction(seq);
			}
}

void StageScene3::calcDamage2(UnitSprite *attacker, TowerSprite* target)	//敵ユニットとプレイヤー領地
{
			target->setHp(target->getHp() - attacker->getAttack());
			if(target->getHp() <= 0){
				auto delay = DelayTime::create(3.0);
				auto callfunc = CallFunc::create([this](){
				//画面移動
					Scene *pScene = GameOver::createScene();
					TransitionFade* transition = TransitionFade::create(1.0f, pScene);
					Director::getInstance()->replaceScene(transition);
				});
			    auto seq = Sequence::create(delay, callfunc, NULL);
			    this->runAction(seq);
			}
}

void StageScene3::Pause(Ref* pSender)
{
	pause = !pause;
	if(pause == true)
		Director::getInstance()->pause();

	else if(pause == false)
		Director::getInstance()->resume();
}

void StageScene3::Menubtn(Ref* pSender)
{
	menu = !menu;
	if(menu == true){
		Director::getInstance()->pause();
		auto menuLayer  = GameMenuLayer::create();
	    menuLayer->setParentScene(this);
	    this->addChild(menuLayer,99999,99999);
	}

	else if(menu == false){
		Director::getInstance()->resume();
	}

}

void StageScene3::onTouchedMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent)
{
//	log("onTouchedMoved");
//	auto diff = touches[0]->getDelta();
//	auto currentPosX = bg->getPositionX();
//	auto dir = (bg->getContentSize().width - VISIBLE_SIZE.width)/2;
//	if(currentPosX > VISIBLE_SIZE.width){
//		bg->setPosition(Point(currentPosX - 10, VISIBLE_SIZE.height/2));
//	}
//	else if(currentPosX < 0){
//		bg->setPosition(Point(currentPosX + 10, VISIBLE_SIZE.height/2));
//	}
//	else
//		bg->setPosition(Point(currentPosX + diff.x, VISIBLE_SIZE.height/2));
}
