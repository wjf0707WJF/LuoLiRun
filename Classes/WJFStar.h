

#ifndef __LuoLiRun__WJFStar__
#define __LuoLiRun__WJFStar__

#include "cocos2d.h"
using namespace cocos2d;

class WJFStar : public Sprite
{
public:
    static WJFStar* createStar(const char* starName);
    int starValue;
    float runSpeed;
private:
    void initStar();
    void update(float delta);
    void onExit();
};

#endif /* defined(__LuoLiRun__WJFStar__) */
