

#include "WJFFlyEnemy.h"

WJFFlyEnemy* WJFFlyEnemy::createEnemyWithName(const char *enemyName)
{
    WJFFlyEnemy *enemy = new WJFFlyEnemy();
    if (enemy && enemy->initWithFile(enemyName)) {
        enemy->initEnemyWithName(enemyName);
        enemy->autorelease();
        return enemy;
    }else{
        CC_SAFE_DELETE(enemy);
        return false;
    }
}

void WJFFlyEnemy::initEnemyWithName(const char *enemyName)
{
    screenSize = Director::getInstance()->getWinSize();
    
    //为enemy创建动画
    this->createAnimate(enemyName, 10);
    
    this->initEnemyPosition();
    
    this->scheduleUpdate();
}

void WJFFlyEnemy::createAnimate(const char *enemyName, int enemyCount)
{
    Animation *animation = Animation::create();
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(enemyName);
    //每个切片的size
    int enemyWidth = this->getContentSize().width/enemyCount;
    int enemyHeight = this->getContentSize().height;
    //循环遍历将贴图中的enemy逐个加入animation
    for (int i = 0; i < enemyCount; i++) {
        animation->addSpriteFrameWithTexture(texture, Rect(i*enemyWidth, 0, enemyWidth, enemyHeight));
    }
    animation->setDelayPerUnit(0.5f);//设置animation的运行一次的时间
    animation->setRestoreOriginalFrame(true);//设置是否回到第一帧
    animation->setLoops(-1);//设置循环次数，-1时为无线循环
    
    Animate *animate = Animate::create(animation);
    this->runAction(animate);
}

void WJFFlyEnemy::initEnemyPosition()
{
    float randomHeight = CCRANDOM_0_1()*300 - 100 + screenSize.height/2;
    this->setPosition(screenSize.width + this->getContentSize().width/2, randomHeight);
}

void WJFFlyEnemy::update(float delta)
{
    this->setPosition(this->getPosition() + Point(-20, 0));
    if (this->getPositionX() < -this->getContentSize().width/2) {
        this->initEnemyPosition();
    }
}

void WJFFlyEnemy::onExit()
{
    this->unscheduleUpdate();
    Sprite::onExit();
}















