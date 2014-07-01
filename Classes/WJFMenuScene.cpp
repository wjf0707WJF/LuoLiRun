

#include "WJFMenuScene.h"
#include "SimpleAudioEngine.h"
#include "WJFAboutScene.h"
#include "WJFGameScene.h"
#include "WJFScoreScene.h"
using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC;

typedef enum
{
    backgroundTag = 0,
    menuTag,
    musicItemTag
}MenuTag;

Scene* WJFMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WJFMenuScene::create();
    scene->addChild(layer);
    return scene;
}


bool WJFMenuScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size screenSize = Director::getInstance()->getWinSize();
    
    //背景音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.mp3");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
    
    //背景图片
    Sprite *background = Sprite::create("MainMenu.png");
    background->setPosition(screenSize.width/2, screenSize.height/2);
    this->addChild(background, 0, backgroundTag);
    
    auto gameItem = MenuItemImage::create("newgameA.png", "newgameB.png", CC_CALLBACK_1(WJFMenuScene::toGameScene, this));
    gameItem->setPosition(screenSize.width-420, screenSize.height-350);
    
    auto continueItem = MenuItemImage::create("continueA.png", "continueB.png", CC_CALLBACK_1(WJFMenuScene::toScoreScene, this));
    continueItem->setPosition(screenSize.width-420, screenSize.height-430);
    
    auto aboutItem = MenuItemImage::create("aboutA.png", "aboutB.png", CC_CALLBACK_1(WJFMenuScene::toAboutScene, this));
    aboutItem->setPosition(screenSize.width-420, screenSize.height-510);
    
    auto menu = Menu::create(gameItem, aboutItem, continueItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1, menuTag);
    
    //控制开关音乐的精灵
    Sprite *musicSprite = Sprite::create("sound-on-A.png");
    musicSprite->setPosition(100, 100);
    this->addChild(musicSprite, 0, musicItemTag);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan=[=](Touch *touch, Event *event)
    {
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect r = Rect(0, 0, s.width, s.height);
        if (r.containsPoint(locationInNode)) {
            this->changeMisc();
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, musicSprite);
    
    return true;
}

void WJFMenuScene::toGameScene(Ref *sender)
{
    TransitionFade *fade = TransitionFade::create(0.5, WJFGameScene::createScene(), Color3B::BLUE);
    Director::getInstance()->replaceScene(fade);
}

void WJFMenuScene::toAboutScene(Ref *sender)
{
    TransitionFade *fade = TransitionFade::create(0.5, WJFAboutScene::createScene(), Color3B::BLUE);
    Director::getInstance()->replaceScene(fade);
}

void WJFMenuScene::toScoreScene(Ref *sender)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    TransitionFlipAngular *fade = TransitionFlipAngular::create(0.5f, WJFScoreScene::createScene());
    Director::getInstance()->replaceScene(fade);
}

void WJFMenuScene::changeMisc()
{
    this->removeChildByTag(musicItemTag);
    Sprite* musicSprite;
    if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        musicSprite = Sprite::create("sound-off-A.png");
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }else{
        musicSprite = Sprite::create("sound-on-A.png");
        SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
    }
    musicSprite->setPosition(100, 100);
    this->addChild(musicSprite, 1, musicItemTag);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan=[=](Touch *touch, Event *event)
    {
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect r = Rect(0, 0, s.width, s.height);
        if (r.containsPoint(locationInNode)) {
            this->changeMisc();
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, musicSprite);
}
















































