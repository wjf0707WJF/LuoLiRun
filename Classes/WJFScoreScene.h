

#ifndef __LuoLiRun__WJFScoreScene__
#define __LuoLiRun__WJFScoreScene__

#include "cocos2d.h"
using namespace cocos2d;

class WJFScoreScene : public Layer
{
public:
    static Scene* createScene();
    
private:
    virtual bool init();
    void backToMenu(Ref *sender);
    
    CREATE_FUNC(WJFScoreScene);
};

#endif /* defined(__LuoLiRun__WJFScoreScene__) */
