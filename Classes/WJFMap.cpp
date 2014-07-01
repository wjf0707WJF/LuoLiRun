

#include "WJFMap.h"
using namespace cocos2d;
USING_NS_CC;

typedef enum
{
    maptag1 = 0,
    maptag2,
}MapTag;

WJFMap* WJFMap::createMap(const char* mapName)
{
    WJFMap *map = new WJFMap();
    if (map && map->init()) {
        map->initMap(mapName);
        map->autorelease();
        return map;
    }else{
        CC_SAFE_DELETE(map);
        return NULL;
    }
}

void WJFMap::initMap(const char* mapName)
{
    
    screenSize = Director::getInstance()->getWinSize();
    Sprite *map1 = Sprite::create(mapName);
    Sprite *map2 = Sprite::create(mapName);
    
    map1->setPosition(Point(map1->getContentSize().width*0.5, screenSize.height*0.5));
    map2->setPosition(Point(map2->getContentSize().width*1.5, screenSize.height*0.5));
    this->addChild(map1, 0, maptag1);
    this->addChild(map2, 0, maptag2);
    
    this->scheduleUpdate();
    
}

void WJFMap::update(float delta)
{

    Sprite *map1 = (Sprite *)this->getChildByTag(maptag1);
    if (map1->getPositionX() <= -map1->getContentSize().width/2) {
        map1->setPosition(map1->getContentSize().width*1.5-5.f, screenSize.height*0.5);
        
    }
    else
    {
        map1->setPosition(map1->getPosition() + Point(-3.f, 0));
    }
    
    Sprite *map2 = (Sprite *)this->getChildByTag(maptag2);
    if (map2->getPositionX() <= -map2->getContentSize().width/2) {
        map2->setPosition(map2->getContentSize().width*1.5-5.f, screenSize.height*0.5);
        
    }
    else
    {
        map2->setPosition(map2->getPosition() + Point(-3.f, 0));
    }
}

void WJFMap::onExit()
{
    this->unscheduleUpdate();
    Layer::onExit();
}























