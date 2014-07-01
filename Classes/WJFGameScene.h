

#ifndef __LuoLiRun__WJFGameScene__
#define __LuoLiRun__WJFGameScene__

#include "cocos2d.h"
using namespace cocos2d;

class WJFGameScene : public Layer
{
public:
    static Scene* createScene();
    static WJFGameScene* getGameScene();
    //获取存放星星的数组
    std::shared_ptr<Vector<Sprite *>> getStarArray();
    std::shared_ptr<Vector<Sprite *>> getLandArray();
    std::shared_ptr<Vector<Sprite *>> getenemyArray();
    void gameOver();
    
private:
    //存放星星的数组，碰撞检测玩家遍历时使用
    std::shared_ptr<Vector<Sprite *>> starArray = std::make_shared<Vector<Sprite *>>();
    std::shared_ptr<Vector<Sprite *>> enemyArray = std::make_shared<Vector<Sprite *>>();
    bool init();
    void starShow(float dt);
    void landShow(float dt);
    std::shared_ptr<Vector<Sprite *>> landArray = std::make_shared<Vector<Sprite *>>();
    CREATE_FUNC(WJFGameScene);
    void backToMenu(Ref *sender);
};

#endif /* defined(__LuoLiRun__WJFGameScene__) */
