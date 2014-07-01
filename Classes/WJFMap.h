

#ifndef __LuoLiRun__WJFMap__
#define __LuoLiRun__WJFMap__

#include "cocos2d.h"
using namespace cocos2d;

class WJFMap : public Layer
{
public:
    static WJFMap* createMap(const char* mapName);
private:
    Size screenSize;
    void initMap(const char* mapName);
    void update(float delta);
    void onExit();
    
    CREATE_FUNC(WJFMap);
};

#endif /* defined(__LuoLiRun__WJFMap__) */
