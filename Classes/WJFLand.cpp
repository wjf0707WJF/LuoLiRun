

#include "WJFLand.h"
#include "WJFGameScene.h"
using namespace cocos2d;
USING_NS_CC;

WJFLand* WJFLand::createLand(const char* landName)
{
    WJFLand *land = new WJFLand();
    if (land && land->initWithFile(landName)) {
        land->initLand();
        land->autorelease();
        return land;
    }else{
        CC_SAFE_DELETE(land);
        return NULL;
    }
}

void WJFLand::initLand()
{
    moveSpeed = 8.0f;
    
    this->scheduleUpdate();
}

void WJFLand::update(float delta)
{
    std::shared_ptr<Vector<Sprite *>> array = WJFGameScene::getGameScene()->getLandArray();
    if (this->getPositionX() < -this->getContentSize().width/2) {
        WJFGameScene::getGameScene()->removeChild(this);
        array->eraseObject(this);
    }else{
        this->setPosition(this->getPosition() + Point(-moveSpeed, 0));
    }
}

void WJFLand::onExit()
{
    this->unscheduleUpdate();
    Sprite::onExit();
}




























