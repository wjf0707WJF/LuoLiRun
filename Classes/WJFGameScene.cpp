

#include "WJFGameScene.h"
#include "WJFMap.h"
#include "WJFStar.h"
#include "WJFLand.h"
#include "WJFPlayer.h"
#include "WJFMenuScene.h"
#include "WJFEnemy.h"
#include "SimpleAudioEngine.h"
#include "WJFFlyEnemy.h"

using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC;

static WJFGameScene* gameScene = NULL;

Scene* WJFGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WJFGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool WJFGameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    gameScene = this;
    Size screenSize = Director::getInstance()->getWinSize();
    
    //初始化进度条
    Sprite *spr = Sprite::create("progressbar.png");
    ProgressTimer *timer = ProgressTimer::create(spr);
    //设置进度条的刷新方式
    timer->setType(ProgressTimer::Type::BAR);
    timer->setAnchorPoint(Point(0, 0.5));
    timer->setMidpoint(Point::ZERO);
    timer->setBarChangeRate(Point(1, 0));
    timer->setScale(0.5);
    timer->setPosition(screenSize.width/2 - 200, screenSize.height/2 + 200);
    //设置百分比为0%
    timer->setPercentage(0);
    this->addChild(timer, 9, 2000);
    
    //设置背景，移动
    WJFMap *map1 = WJFMap::createMap("back_1.png");
    this->addChild(map1, 0, 1);
    WJFMap *map2 = WJFMap::createMap("back_5.png");
    this->addChild(map2, 1, 2);
    
    //每隔一段时间生成一个星星
    this->schedule(schedule_selector(WJFGameScene::starShow), 1.5);
    
    //起始位置初始化land
    for (int i = 0; i < 10; i++) {
        WJFLand *land = WJFLand::createLand("road_5.png");
        landArray->pushBack(land);
        Size landSize = land->getContentSize();
        land->setPosition(landSize.width*i + landSize.width/2, screenSize.height/2 - 125);
        this->addChild(land, 2, 3);
    }
    
    this->schedule(schedule_selector(WJFGameScene::landShow), 2.0f);
    
    //创建主角精灵
    WJFPlayer *player = WJFPlayer::createPlayer("s_jump.png");
    this->addChild(player, 9, 4);
    
    //创建飞行的敌人
    WJFFlyEnemy *enemy = WJFFlyEnemy::createEnemyWithName("enemy_duck.png");
    this->addChild(enemy, 9, 1000);
    
    return true;
}

WJFGameScene* WJFGameScene::getGameScene()
{
    return gameScene;
}

void WJFGameScene::starShow(float dt)
{
    Size screenSize = Director::getInstance()->getWinSize();
    
//    int starNum = CCRANDOM_0_1()*5;
    int stye = CCRANDOM_0_1()*3.5;
    int randomHeight = CCRANDOM_0_1()*50 + 50;
    for (int i = 0; i < 5; i++) {
        WJFStar *star = WJFStar::createStar("star.png");
        starArray->pushBack(star);
        this->addChild(star, 2, 3);
        star->setScale(0.5);
        Size starSize = star->getContentSize();
        switch (stye) {
            case 0:
            {
                star->setPosition(screenSize.width+starSize.width/2+(starSize.width-20)*i, screenSize.height/2 + randomHeight);
            }
                break;
            case 1:
            {
                if (i <= 2) {
                    star->setPosition(screenSize.width+starSize.width/2+(starSize.width-20)*i, screenSize.height/2 + randomHeight + (starSize.height-20) * i);
                }else
                {
                    star->setPosition(screenSize.width+starSize.width/2+(starSize.width-20)*i, screenSize.height/2 + randomHeight + (starSize.height-20) * (4-i));
                }
            }
                break;
            case 2:
            {
                if (i <= 2) {
                    star->setPosition(screenSize.width+starSize.width/2+(starSize.width-20)*i, screenSize.height/2 - randomHeight+ (starSize.height-20) * (4-i));
                }else{
                    star->setPosition(screenSize.width+starSize.width/2+(starSize.width-20)*i, screenSize.height/2 - randomHeight+ (starSize.height-20) * i);
                }
            }
                break;
            case 3:
            {
                if (i % 2 == 1) {
                    star->setPosition(screenSize.width+starSize.width/2+(starSize.width-20)*i, screenSize.height/2);
                }else{
                    star->setPosition(screenSize.width+starSize.width/2+(starSize.width-20)*i, screenSize.height/2 + (starSize.height-20));
                }
            }
                break;
        }
    }
}

std::shared_ptr<Vector<Sprite *>> WJFGameScene::getStarArray()
{
    return starArray;
}

void WJFGameScene::landShow(float dt)
{
    Size screenSize = Director::getInstance()->getWinSize();
    int stye = CCRANDOM_0_1()*1.5;
    int randomNum = CCRANDOM_0_1()*2.5 + 1;
    for (int i = 0; i < randomNum; i++) {
        int randomHeight = CCRANDOM_0_1()*100;
        WJFLand *land = WJFLand::createLand("road_5.png");
        landArray->pushBack(land);
        Size landSize = land->getContentSize();
        switch (stye) {
            case 0:
                land->setPosition(screenSize.width + landSize.width/2 + landSize.width*i, screenSize.height/2 - 125 +randomHeight);
                break;
            case 1:
                land->setPosition(screenSize.width + landSize.width/2 + landSize.width*i, screenSize.height/2 - 125 - landSize.height/2*i + randomHeight);
                break;
        }
        
        //添加仙人掌
        if (randomNum == 3 && i == 2) {
            WJFEnemy *enemy = WJFEnemy::createEnemy("enemy.png");
            enemyArray->pushBack(enemy);
            enemy->setScale(0.7);
            this->addChild(enemy, 3, 4);
            enemy->setPosition(land->getPositionX(), land->getPositionY() + enemy->getContentSize().height/2+10);
        }
        
        this->addChild(land, 2, 3);
    }
}

std::shared_ptr<Vector<Sprite *>> WJFGameScene::getLandArray()
{
    return landArray;
}

std::shared_ptr<Vector<Sprite *>> WJFGameScene::getenemyArray()
{
    return enemyArray;
}

//游戏结束函数
void WJFGameScene::gameOver()
{
    //添加失败场景
    Size screenSize = Director::getInstance()->getWinSize();
    LayerColor *layer = LayerColor::create(Color4B(0, 0, 0, 190), screenSize.width, screenSize.height);
    Sprite *lostSprite = Sprite::create("gameover.png");
    lostSprite->setPosition(screenSize.width/2, screenSize.height/2 + 100);
    layer->addChild(lostSprite);
    this->addChild(layer, 10, 4);
    
    //添加一个返回主界面的按钮
    Label *toMenu = Label::createWithSystemFont("返回主菜单", "Helvetica-Bold", 30);
    MenuItemLabel *menuLabel = MenuItemLabel::create(toMenu, CC_CALLBACK_1(WJFGameScene::backToMenu, this));
    menuLabel->setPosition(screenSize.width/2, screenSize.height/2 - 100);
    Menu *menu = Menu::create(menuLabel, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 10, 4);
    
    //暂停游戏
    Director::getInstance()->pause();
}

void WJFGameScene::backToMenu(Ref *sender)
{
    this->unscheduleUpdate();
    //继续游戏
    Director::getInstance()->resume();
    //返回主界面
    return Director::getInstance()->replaceScene(WJFMenuScene::createScene());
}

















