#include "HelloWorldScene.h"
#include "TowerSprite.h"

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
    if ( !Layer::init() )           //init�̓Q�[��������������Ƃ��Ɏg���֐��B�C���X�^���X���Q�[����ʁB
    {
        return false;
    }
    
    //aiueo kakikukeko
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    createInitObjects();

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

    //�{�^���̐����i�摜�j
     //��ʃT�C�Y�̎擾
     Size winSize = Director::getInstance()->getWinSize();
     auto pBtnItem1 = MenuItemImage::create("images/btn1.png","btn1.png", CC_CALLBACK_1(HelloWorld::addPlayer, this));
     auto pBtnItem2 = MenuItemImage::create("images/btn2.png","btn2.png", CC_CALLBACK_1(HelloWorld::addPlayer2, this));
     auto pBtnItem3 = MenuItemImage::create("images/btn3.png","btn3.png", CC_CALLBACK_1(HelloWorld::addPlayer3, this));
     pBtnItem1 -> setPosition(Point(0,100));
     pBtnItem2 -> setPosition(Point(100,100));
     pBtnItem3 -> setPosition(Point(200,100));
     Menu *pMenu = Menu::create(pBtnItem1,pBtnItem2,pBtnItem3, NULL);
     pMenu->setPosition(Point(winSize.width/2,0));
     this->addChild(pMenu);

    //�X�P�W���[���A�b�v�f�[�g���X�^�[�g
    this->scheduleUpdate();

    return true;
}


//����I�ɍ����ɌĂ΂��֐�
void HelloWorld::update(float delta)
 {
    log("update");
    if(frame % 40 == 0){
    	addEnemy();
    }
    collisionChecker();
    collisionChecker2();
    frame++;
}

void HelloWorld::addEnemy()
{
	//�G�l�~�[�̒ǉ�
		    auto enemy = Sprite::create("images/missile1.png");
		    enemy->setPosition(territory2->getPosition());
		    this->addChild(enemy);

		    enemyVect.pushBack(enemy);

		    auto move = MoveTo::create(5.0f, territory->getPosition());
		    enemy->runAction(move);
}
void HelloWorld::createInitObjects()
{
	//�Q�[���w�i�̒ǉ�
	    auto bg = Sprite::create("images/bg.png");
	         bg->setPosition(Point(640/2, 1136/2));
	         bg->setScale(2.5);
	         bg->setRotation(90);
	         this->addChild(bg);

	//�v���C���[�̒n�̒ǉ�
	    territory = TowerSprite::create("images/player1_1.png");
	    territory->setPosition(Point(640/4, 1136/3));
	    territory->setScale(1.5);
	    territory->setRotation(90);
	    territory->setHp(100);
	    this->addChild(territory);

	    log("HP��:%d",territory->getHp());

	 //�G�l�~�[�̒n�̒ǉ�
	    territory2 = TowerSprite::create("images/enemy1_1.png");
	    territory2->setPosition(Point(1600, 1136/3));
	    territory2->setScale(1.5);
	    territory2->setRotation(-90);
	    this->addChild(territory2);
}

void HelloWorld::addPlayer(Ref * sender)
{
	//�v���C���[�̒ǉ�
	    auto player = Sprite::create("images/missile2.png");
	    player->setPosition(territory->getPosition());
	    this->addChild(player);

	    playerVect.pushBack(player);

	    auto move = MoveTo::create(5.0f, territory2->getPosition());
	    /*auto callfunc = CallFunc::create([=](){
	    	player->removeFromParent();
	    	playerVect.eraseObject(player);
	    });
	    auto seq = Sequence::create(move, callfunc, NULL);*/
	    player->runAction(move);
}

void HelloWorld::addPlayer2(Ref * sender)
{
	//�v���C���[�̒ǉ�
	    auto player = Sprite::create("images/missile3.png");
	    player->setPosition(territory->getPosition());
	    this->addChild(player);

	    playerVect2.pushBack(player);

	    auto move = MoveTo::create(5.0f, territory2->getPosition());
	    /*auto callfunc = CallFunc::create([=](){
	    	player->removeFromParent();
	    	playerVect2.eraseObject(player);
	    });
	    auto seq = Sequence::create(move, callfunc, NULL);*/
	    player->runAction(move);
}

void HelloWorld::addPlayer3(Ref * sender)
{
	//�v���C���[�̒ǉ�
	    auto player = Sprite::create("images/missile4.png");
	    player->setPosition(territory->getPosition());
	    this->addChild(player);

	    playerVect3.pushBack(player);

	    auto move = MoveTo::create(5.0f, territory2->getPosition());
	    /*auto callfunc = CallFunc::create([=](){
	    	player->removeFromParent();
	    	playerVect3.eraseObject(player);
	    });
	    auto seq = Sequence::create(move, callfunc, NULL);*/
	    player->runAction(move);
}

void HelloWorld::collisionChecker()		//���j�b�g���m�̏Փ˔���
{
	//�v���C���[�̓G�Ƃ̏Փ˔���
	for(Sprite * player : playerVect){
		for(Sprite * enemy : enemyVect){
			if(player->getBoundingBox().intersectsRect(enemy->getBoundingBox())){
				//player->attackForTarget(enemy);		//�ʃN���X�̌Ăяo����
				enemy->removeFromParent();		//�G����ʂ��珜��
				enemyVect.eraseObject(enemy);	//�G��z�񂩂珜��

				break;
			}
		}
	}
	//�v���C���[�̓G�Ƃ̏Փ˔���
	for(Sprite * player2 : playerVect2){
		for(Sprite * enemy : enemyVect){
			if(player2->getBoundingBox().intersectsRect(enemy->getBoundingBox())){
				//player->attackForTarget(enemy);		//�ʃN���X�̌Ăяo����
				enemy->removeFromParent();		//�G����ʂ��珜��
				enemyVect.eraseObject(enemy);	//�G��z�񂩂珜��

				break;
			}
		}
	}
	//�v���C���[�̓G�Ƃ̏Փ˔���
	for(Sprite * player3 : playerVect3){
		for(Sprite * enemy : enemyVect){
			if(player3->getBoundingBox().intersectsRect(enemy->getBoundingBox())){
				//player->attackForTarget(enemy);		//�ʃN���X�̌Ăяo����
				enemy->removeFromParent();		//�G����ʂ��珜��
				enemyVect.eraseObject(enemy);	//�G��z�񂩂珜��

				break;
			}
		}
	}
}

void HelloWorld::collisionChecker2()		//���j�b�g�Ɨ̒n�̏Փ˔���
{
	//�v���C���[���j�b�g�ƓG�̒n�̏Փ˔���
	for(Sprite * player : playerVect){
		if(player->getBoundingBox().intersectsRect(territory2->getBoundingBox())){
			player->removeFromParent();		//�v���C���[����ʂ��珜��
			playerVect.eraseObject(player);	//�v���C���[��z�񂩂珜��

			calcDamage(player, territory2);

			break;
		}
	}
	//�v���C���[���j�b�g�ƓG�̒n�̏Փ˔���
	for(Sprite * player2 : playerVect2){
		if(player2->getBoundingBox().intersectsRect(territory2->getBoundingBox())){
			player2->removeFromParent();		//�v���C���[����ʂ��珜��
			playerVect2.eraseObject(player2);	//�v���C���[��z�񂩂珜��

			break;
		}
	}
	//�v���C���[���j�b�g�ƓG�̒n�̏Փ˔���
	for(Sprite * player3 : playerVect3){
		if(player3->getBoundingBox().intersectsRect(territory2->getBoundingBox())){
			player3->removeFromParent();		//�v���C���[����ʂ��珜��
			playerVect3.eraseObject(player3);	//�v���C���[��z�񂩂珜��

			break;
		}
	}
	//�G���j�b�g�ƃv���C���[�̒n�̏Փ˔���
	for(Sprite * enemy : enemyVect){
		if(enemy->getBoundingBox().intersectsRect(territory->getBoundingBox())){
			enemy->removeFromParent();		//�G����ʂ��珜��
			enemyVect.eraseObject(enemy);	//�G��z�񂩂珜��

			break;
		}
	}
}

void HelloWorld::calcDamage(Sprite *attacker, TowerSprite* target)
{
			//�T�E���h�Đ�

			//�p�[�e�B�N�����o��


			target->setHp(target->getHp() - 10);
			//target->setHp(target->getHp() - attacker->getAttackValue());
			if(target->getHp() == 0){
				target->removeFromParent();
			}
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
