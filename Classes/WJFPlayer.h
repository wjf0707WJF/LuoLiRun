

#ifndef __LuoLiRun__WJFPlayer__
#define __LuoLiRun__WJFPlayer__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

//自定义函数模板, 主要用于将int float 等数字转换成strng字符串
template <typename T>
string Convert2String(const T &value)
{
    stringstream ss;
    ss << value;
    return ss.str();
}

class WJFPlayer : public Sprite
{
public:
    static WJFPlayer* createPlayer(const char* playerName);
private:
    float score;//获得分数
    float meter;//距离
    float speed;
    float gravity;
    bool iscollisionWithLand;
    int jumpNum;
    
    RepeatForever *repeat;
    Texture2D *jump;
    Texture2D *hurt;
    Texture2D *run;
    int state;//0:奔跑, //1:置空, //2:受伤
    
    bool isOver;
    
    int strongCount;//无敌时间
    
    void initPlayer();
    void update(float delta);
    void collisionWithStar();
    void collisionWithFlyEnemy();
    void playerDrop();
    void onExit();
    void isDie(float delta);
    void playerListener();
    void addScore(int value);
    void addMeter(float distance);
    void playerState(float delta);
    
};

#endif /* defined(__LuoLiRun__WJFPlayer__) */
