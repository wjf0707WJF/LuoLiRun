

#include "WJFEnemy.h"
#include "WJFGameScene.h"
USING_NS_CC;

WJFEnemy* WJFEnemy::createEnemy(const char *enemyName)
{
    WJFEnemy *enemy = new WJFEnemy();
    if (enemy && enemy->initWithFile(enemyName)) {
        enemy->initEnemy();
        enemy->autorelease();
        return enemy;
    }else{
        CC_SAFE_DELETE(enemy);
        return NULL;
    }
}

void WJFEnemy::initEnemy()
{
    this->scheduleUpdate();
}

void WJFEnemy::update(float delta)
{
    this->setPosition(this->getPosition() + Point(-8.0f, 0));
    if (this->getPositionX() <= -this->getContentSize().width/2) {
        std::shared_ptr<Vector<Sprite *>> enemyArray = WJFGameScene::getGameScene()->getenemyArray();
        WJFGameScene::getGameScene()->removeChild(this);
        enemyArray->eraseObject(this);
    }
}

void WJFEnemy::onExit()
{
    Sprite::onExit();
    this->unscheduleUpdate();
}









