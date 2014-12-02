#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )           //initはゲームを初期化するときに使う関数。インスタンス＝ゲーム画面。
    {
        return false;
    }
    
    //aiueo kakikukeko
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //ゲーム背景の追加
    auto bg = Sprite::create("images/bg.png");
         bg->setPosition(Point(640/2, 1136/2));
         bg->setScale(2.5);
         bg->setRotation(90);
         this->addChild(bg);

    //領地の追加
    auto territory = Sprite::create("images/player1_1.png");
    territory->setPosition(Point(640/4, 1136/3));
    territory->setScale(1.5);
    territory->setRotation(90);
    this->addChild(territory);

    //プレイヤーの追加
    auto player = Sprite::create("images/missile2.png");
    player->setPosition(territory->getPosition());
    this->addChild(player);
    auto move = MoveBy::create(5.0f, Point(1200, 0));
    player->runAction(move);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");  //画像の生成

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));      //画像の位置

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);                      //画像を画面に貼り付け


    Size winSize = Director::getInstance()->getWinSize();
    LabelTTF *retryLabel = LabelTTF::create("Retry2", "Arial", 24.0);
    retryLabel->setColor(Color3B::WHITE);                                     //③
    //retryLabel->enableShadow(Color4B::RED,Size(-2,-4),2);
    MenuItemLabel *retryItem = MenuItemLabel::create(retryLabel, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    retryItem->setPosition(Point(0, 0));
    Menu *menu2 = Menu::create(retryItem, NULL);
    menu2->setPosition(Point(100, 100));
    this->addChild(menu2);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
