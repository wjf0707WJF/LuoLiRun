

#include "WJFStar.h"
#include "WJFGameScene.h"

WJFStar* WJFStar::createStar(const char* starName)
{
    WJFStar *star = new WJFStar();
    if (star && star->initWithFile(starName)) {
        star->initStar();
        star->autorelease();
        return star;
    }else{
        CC_SAFE_DELETE(star);
        return NULL;
    }
}

void WJFStar::initStar()
{
    starValue = 10;
    runSpeed =8.0f;
    
//    this->setScale(0.5);
//    Size screenSize = Director::getInstance()->getWinSize();
//    this->setPosition(screenSize.width + this->getContentSize().width, screenSize.height/2 + 100);
    
    this->scheduleUpdate();
}

void WJFStar::update(float delta)
{
    std::shared_ptr<Vector<Sprite *>> array = WJFGameScene::getGameScene()->getStarArray();
    if (this->getPositionX() < -this->getContentSize().width/2) {
        WJFGameScene::getGameScene()->removeChild(this);
        array->eraseObject(this);
    }else{
        this->setPosition(this->getPosition() + Point(-runSpeed, 0));
    }
}

void WJFStar::onExit()
{
    this->unscheduleUpdate();
    Sprite::onExit();
}
































