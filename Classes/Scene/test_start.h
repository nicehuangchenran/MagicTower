
#ifndef test_start_hpp
#define test_start_hpp

#include "cocos2d.h"
class test_start:public cocos2d::Scene
{
public:
    cocos2d::TMXTiledMap* _tileMap;
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(test_start);
};

#endif /* test_start_h */
