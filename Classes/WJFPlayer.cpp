

#include <math.h>
#include "WJFPlayer.h"
#include "WJFGameScene.h"
#include "WJFStar.h"
#include "WJFLand.h"
#include "WJFEnemy.h"
#include "WJFFlyEnemy.h"

using namespace cocos2d;
USING_NS_CC;

WJFPlayer* WJFPlayer::createPlayer(const char* playerName)
{
    WJFPlayer* player = new WJFPlayer();
    if (player && player->initWithFile(playerName))
    {
        player->initPlayer();
        player->autorelease();
        return player;
    }else
    {
        CC_SAFE_DELETE(player);
        return NULL;
    }
}

void WJFPlayer::initPlayer()
{
    Size screenSize = Director::getInstance()->getWinSize();
    
    state = 0;//初始主角精灵的状态为置空
    
    score = 0;
    meter = 0;
    isOver = false;
    speed = -4.0f;
    gravity = 1.3f;
    iscollisionWithLand = false;
    jumpNum = 0;
    strongCount = 0;
    
    //初始化“分数”文字加入layer中
    Label *label = Label::createWithBMFont("ziti.fnt", "Score:");
    label->setScale(0.5);
    label->setPosition(50, screenSize.height/2 + 200);
    WJFGameScene::getGameScene()->addChild(label, 2);
    
    //将Score加入分数中
    std::string strScore = Convert2String(score);
    Label *labelScore = Label::createWithBMFont("ziti.fnt", strScore.c_str());
    labelScore->setScale(0.5);
    labelScore->setPosition(140, screenSize.height/2 + 200);
    WJFGameScene::getGameScene()->addChild(labelScore, 2, 10);
    
    //初始化“米数”文字加入layer中
    Label *meterLabel = Label::createWithBMFont("ziti.fnt", "Distance");
    meterLabel->setScale(0.5);
    meterLabel->setPosition(70, screenSize.height/2 + 170);
    WJFGameScene::getGameScene()->addChild(meterLabel, 2);
    
    //初始化“米数”文字加入layer中
    Label *mi = Label::createWithBMFont("ziti.fnt", "M");
    mi->setScale(0.5);
    mi->setPosition(240, screenSize.height/2 + 170);
    WJFGameScene::getGameScene()->addChild(mi, 2);
    
    //将meter加入距离中
    std::string meterString = Convert2String(meter);
    Label *meterShow = Label::createWithBMFont("ziti.fnt", meterString.c_str());
    meterShow->setScale(0.5);
    meterShow->setPosition(180, screenSize.height/2 + 170);
    WJFGameScene::getGameScene()->addChild(meterShow, 2, 20);
    
    Sprite *obj = Sprite::create("s_jump.png");
    jump = obj->getTexture();
    obj = Sprite::create("s_hurt.png");
    hurt = obj->getTexture();
    obj = Sprite::create("s_1.png");
    run = obj->getTexture();
    
    //加载纹理贴图
//    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
//    frameCache->addSpriteFramesWithFile("sprite.plist");
//    Vector<SpriteFrame *> frames;
//    for (int i = 1; i < 7; i++) {
//        __String *file = __String::createWithFormat("s_%d.png", i);
//        SpriteFrame *frame = frameCache->getSpriteFrameByName(file->getCString());
//        frames.pushBack(frame);
//    }
    Animation *animation = Animation::create();
    animation->addSpriteFrameWithFileName("s_1.png");
    animation->addSpriteFrameWithFileName("s_2.png");
    animation->addSpriteFrameWithFileName("s_3.png");
    animation->addSpriteFrameWithFileName("s_4.png");
    animation->addSpriteFrameWithFileName("s_5.png");
    animation->addSpriteFrameWithFileName("s_6.png");
    animation->setDelayPerUnit(0.15f);
    animation->setRestoreOriginalFrame(true);
    
    Animate *animate = Animate::create(animation);
    repeat = RepeatForever::create(animate);
    this->runAction(repeat);
    
    this->setScale(0.5f);
    this->setPosition(200, screenSize.height/2 + 250);
    this->scheduleUpdate();
}

void WJFPlayer::update(float delta)
{
    //与flyEnemy的碰撞检测
    this->collisionWithFlyEnemy();
    //与星星的碰撞检测
    this->collisionWithStar();
    //逐帧掉落
    this->playerDrop();
    //检测主角是否死亡
    this->isDie(delta);
    //逐帧监测player的状态
    this->playerState(delta);
}

void WJFPlayer::collisionWithFlyEnemy()
{
    WJFFlyEnemy *enemy = (WJFFlyEnemy *)WJFGameScene::getGameScene()->getChildByTag(1000);
    
    if (this->boundingBox().intersectsRect(enemy->boundingBox()) &&
        abs(this->getPositionX()-enemy->getPositionX()) < this->getContentSize().width/2 + enemy->getContentSize().width/2 - 80 &&
        abs(this->getPositionY() - enemy->getPositionY()) < this->getContentSize().height/2 + enemy->getContentSize().height/2 - 80) {
        state = 2;
        isOver = true;
        _eventDispatcher->removeAllEventListeners();
        this->unscheduleUpdate();
        WJFGameScene::getGameScene()->gameOver();
    }
}

void WJFPlayer::playerState(float delta)
{
    switch (state) {
        case 1:
            this->stopAllActions();
            this->setTexture(jump);
            break;
        case 2:
            this->stopAllActions();
            this->setTexture(hurt);
            break;
        case 0:
        {
            if (this->getNumberOfRunningActions() == 0) {
                Animation *animation = Animation::create();
                animation->addSpriteFrameWithFileName("s_1.png");
                animation->addSpriteFrameWithFileName("s_2.png");
                animation->addSpriteFrameWithFileName("s_3.png");
                animation->addSpriteFrameWithFileName("s_4.png");
                animation->addSpriteFrameWithFileName("s_5.png");
                animation->addSpriteFrameWithFileName("s_6.png");
                animation->setDelayPerUnit(0.15f);
                animation->setRestoreOriginalFrame(true);
                Animate *animate = Animate::create(animation);
                repeat = RepeatForever::create(animate);
                this->runAction(repeat);
            }
            break;
        }
    }
}

//和星星碰撞检测
void WJFPlayer::collisionWithStar()
{
    std::shared_ptr<Vector<Sprite *>> starArray = WJFGameScene::getGameScene()->getStarArray();
    int starNum = starArray->size();
    for (int i = 0; i < starNum; i++)
    {
        WJFStar *star = (WJFStar *)starArray->at(i);
        if (star->boundingBox().intersectsRect(this->boundingBox()))
        {
            this->addScore(star->starValue);
            
            //吃星星的离子效果
            ParticleSystemQuad *particle = ParticleSystemQuad::create("particle_boom.plist");
            particle->setPosition(star->getPosition());
            particle->setAutoRemoveOnFinish(true);
            WJFGameScene::getGameScene()->addChild(particle, 9);
            
            WJFGameScene::getGameScene()->removeChild(star);
            starArray->eraseObject(star);
            break;
        }
    }
}

//主角精灵掉落函数
void WJFPlayer::playerDrop()
{
    speed -= gravity;
    std::shared_ptr<Vector<Sprite *>> landArray = WJFGameScene::getGameScene()->getLandArray();
    int landNum = landArray->size();
    WJFLand *landNow;
    for (int i = 0; i < landNum; i++)
    {
        WJFFlyEnemy *enemy = (WJFFlyEnemy *)WJFGameScene::getGameScene()->getChildByTag(1000);
        WJFLand *land = (WJFLand *)landArray->at(i);
        if (!this->boundingBox().intersectsRect(enemy->boundingBox()) &&
            this->getPositionY() - 10 > land->getPositionY() &&
            abs(this->getPositionX()-land->getPositionX()) <= land->getContentSize().width/2+this->getContentSize().width/2-100 &&
            abs(this->getPositionY()-land->getPositionY()) <= this->getContentSize().height/4+land->getContentSize().height/2-20)
        {
            landNow = land;
            iscollisionWithLand = true;
            speed = -8.0f;
            break;
        }else
        {
            if (i == landNum-1)
            {
                iscollisionWithLand = false;
            }
        }
    }
    
    if (iscollisionWithLand)
    {
        this->setPosition(200, landNow->getPositionY()+landNow->getTexture()->getContentSize().height/2 + 30);
        state = 0;//当主角与地面碰撞后，设置主角精灵的状态为run
        //主角跳跃
        this->playerListener();
        //当只跳跃一次，并且落地后，跳跃次数设为0
        if (jumpNum == 1)
        {
            jumpNum = 0;
        }
    }else
    {
        this->setPosition(this->getPosition() + Point(0, speed));
        if (jumpNum >= 2) {
            jumpNum = 0;
            _eventDispatcher->removeAllEventListeners();
        }
    }
}

void WJFPlayer::isDie(float delta)
{
    if (this->getPositionY() < -this->getContentSize().height/2)
    {
        isOver = true;
        this->unscheduleUpdate();
        _eventDispatcher->removeAllEventListeners();
        WJFGameScene::getGameScene()->gameOver();
    }else
    {
        float distance = delta * 8.0f;
        this->addMeter(distance);
    }
    
    
    //和enemy碰撞检测
    std::shared_ptr<Vector<Sprite *>> enemyArray = WJFGameScene::getGameScene()->getenemyArray();
    int enemyNum = enemyArray->size();
    for (int i = 0; i < enemyNum; i++) {
        WJFEnemy *enemy = (WJFEnemy *)enemyArray->at(i);
        if (abs(enemy->getPositionX()-this->getPositionX()) <= enemy->getContentSize().width/2+this->getContentSize().width/2 - 100 &&
            abs(enemy->getPositionY()-this->getPositionY()) <= enemy->getContentSize().height/2+this->getContentSize().height/2 - 150)
        {
            state = 2;//设置主角精灵的状态为受伤
            
            this->stopAllActions();
            _eventDispatcher->removeAllEventListeners();
            this->unscheduleUpdate();
            WJFGameScene::getGameScene()->gameOver();
        }
    }
}

void WJFPlayer::playerListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->setEnabled(true);
    listener->onTouchBegan=[=](Touch *touch, Event *event)
    {
        state = 1;//设置主角精灵状态为置空
        
        speed = 18.0f;
        speed -= gravity;
        
        jumpNum++;
        
        this->setPosition(this->getPosition() + Point(0, speed));
        
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, WJFGameScene::getGameScene());
    
}

//增加积分
void WJFPlayer::addScore(int value)
{
    score += value;
    std::string strScore = Convert2String(score);
    Label *labelScore = (Label *)WJFGameScene::getGameScene()->getChildByTag(10);
    labelScore->setString(strScore.c_str());
    
    
    ProgressTimer *timer = (ProgressTimer *)WJFGameScene::getGameScene()->getChildByTag(2000);
    timer->setPercentage(timer->getPercentage() + 10);
    
    //当能量条满的时候，将能量条归零
    if (timer->getPercentage() >= 100) {
        
        timer->setPercentage(0);
    }
}

void WJFPlayer::addMeter(float distance)
{
    meter += distance;
    std::string runMeter = Convert2String((int)meter);
    Label *labelMeter = (Label *)WJFGameScene::getGameScene()->getChildByTag(20);
    labelMeter->setString(runMeter.c_str());
}


void WJFPlayer::onExit()
{
    Sprite::onExit();
    this->unscheduleUpdate();
}





























