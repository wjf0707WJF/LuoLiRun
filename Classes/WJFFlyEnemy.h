

#ifndef __LuoLiRun__WJFFlyEnemy__
#define __LuoLiRun__WJFFlyEnemy__

#include "cocos2d.h"
using namespace cocos2d;

class WJFFlyEnemy : public Sprite
{
public:
    //实例化enemy函数
    static WJFFlyEnemy* createEnemyWithName(const char *enemyName);
    
private:
    Size screenSize;
    
    void initEnemyWithName(const char *enemyName);
    
    void createAnimate(const char *enemyName, int enemyCount);
    void update(float delta);
    void initEnemyPosition();
    void onExit();
};

#endif /* defined(__LuoLiRun__WJFFlyEnemy__) */
