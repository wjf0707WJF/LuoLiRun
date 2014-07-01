

#ifndef __LuoLiRun__WJFMenuScene__
#define __LuoLiRun__WJFMenuScene__

#include "cocos2d.h"

using namespace cocos2d;

class WJFMenuScene : public Layer
{
public:
    static Scene* createScene();
    
private:
    virtual bool init();
    
    void toGameScene(Ref *sender);
    void toAboutScene(Ref *sender);
    void toScoreScene(Ref *sender);
    void changeMisc();
    
    CREATE_FUNC(WJFMenuScene);
};

#endif /* defined(__LuoLiRun__WJFMenuScene__) */
