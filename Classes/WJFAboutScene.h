

#ifndef __LuoLiRun__WJFAboutScene__
#define __LuoLiRun__WJFAboutScene__

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

class WJFAboutScene : public Layer
{
public:
    static Scene* createScene();
private:
    bool init();
    void backToMenu(Ref *sender);
    
    CREATE_FUNC(WJFAboutScene);
};

#endif /* defined(__LuoLiRun__WJFAboutScene__) */
