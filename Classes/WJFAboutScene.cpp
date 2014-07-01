

#include "WJFAboutScene.h"
#include "WJFMenuScene.h"

using namespace cocos2d;
USING_NS_CC;

Scene* WJFAboutScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WJFAboutScene::create();
    scene->addChild(layer);
    return scene;
}

bool WJFAboutScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size screenSize = Director::getInstance()->getWinSize();
    
    Sprite *background = Sprite::create("tb.png");
    background->setPosition(screenSize.width/2, screenSize.height/2);
    background->setRotation(90);
    this->addChild(background, 0, 0);
    
    auto backToMenuItem = MenuItemImage::create("backA.png", "backB.png", CC_CALLBACK_1(WJFAboutScene::backToMenu, this));
    backToMenuItem->setPosition(screenSize.width-40, 40);
    
    auto menu = Menu::create(backToMenuItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1, 0);
    
    Sprite *about = Sprite::create("about.png");
    about->setPosition(screenSize.width/2, screenSize.height/2 + 200);
    this->addChild(about, 1, 0);
    
    //添加作者，时间，说明
    Label *labelName = Label::createWithSystemFont("作者: 王建峰", "Arial", 28);
    Label *labelTime = Label::createWithSystemFont("时间:2014-06-27", "Arial", 28);
    Label *labelExplain = Label::createWithSystemFont("此项目为个人制作源码, 图片素材来源于网络, 不用于任何商业用途!", "Arial", 28);
    labelExplain->setWidth(500);
    labelName->setPosition(screenSize.width/2, screenSize.height/2 + 100);
    labelTime->setPosition(screenSize.width/2, screenSize.height/2);
    labelExplain->setPosition(screenSize.width/2, screenSize.height/2-100);
    labelName->setColor(Color3B::RED);
    labelTime->setColor(Color3B::RED);
    labelExplain->setColor(Color3B::RED);
    this->addChild(labelName, 2, 1);
    this->addChild(labelTime, 2, 2);
    this->addChild(labelExplain, 2, 3);
    
    return true;
}

void WJFAboutScene::backToMenu(Ref *sender)
{
    TransitionFade *fade = TransitionFade::create(0.5, WJFMenuScene::createScene(), Color3B::BLUE);
    Director::getInstance()->replaceScene(fade);
}






