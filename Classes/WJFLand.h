

#ifndef __LuoLiRun__WJFLand__
#define __LuoLiRun__WJFLand__

#include "cocos2d.h"
using namespace cocos2d;

class WJFLand : public Sprite
{
public:
    static WJFLand* createLand(const char* landName);
    float moveSpeed;
private:
    void initLand();
    void update(float delta);
    void onExit();
};

#endif /* defined(__LuoLiRun__WJFLand__) */
