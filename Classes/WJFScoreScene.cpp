

#include "WJFScoreScene.h"
#include "WJFMenuScene.h"

Scene* WJFScoreScene::createScene()
{
    auto scene = Scene::create();
    auto layer =WJFScoreScene::create();
    scene->addChild(layer);
    return scene;
}

bool WJFScoreScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size screenSize = Director::getInstance()->getWinSize();
    
    Sprite *background = Sprite::create("back_1.png");
    background->setPosition(screenSize.width/2, screenSize.height/2);
    this->addChild(background);
    
    Sprite *background1 = Sprite::create("back_5.png");
    background1->setPosition(screenSize.width/2, screenSize.height/2);
    this->addChild(background1);
    
    Label *backMain = Label::createWithBMFont("stye.fnt", "Back To Menu");
    MenuItemLabel *backLabel = MenuItemLabel::create(backMain, CC_CALLBACK_1(WJFScoreScene::backToMenu, this));
    backLabel->setPosition(screenSize.width/2, screenSize.height/2 - 200);
    Menu *menu = Menu::create(backLabel, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
    
    return true;
}

void WJFScoreScene::backToMenu(Ref *sender)
{
    Director::getInstance()->replaceScene(TransitionFadeUp::create(1.5f, WJFMenuScene::createScene()));
}


































