

#ifndef __LuoLiRun__WJFEnemy__
#define __LuoLiRun__WJFEnemy__

#include "cocos2d.h"
using namespace cocos2d;

class WJFEnemy : public Sprite
{
public:
    static WJFEnemy* createEnemy(const char *enemyName);
private:
    void initEnemy();
    void update(float delta);
    void onExit();
};

#endif /* defined(__LuoLiRun__WJFEnemy__) */
