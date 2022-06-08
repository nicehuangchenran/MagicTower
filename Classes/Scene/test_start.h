#ifndef _TEST_START_H_
#define _TEST_START_H_

#include "cocos2d.h"
class test_start:public cocos2d::Scene
{
public:
    cocos2d::TMXTiledMap* _tileMap;
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(test_start);
};

#endif // !_TEST_START_H_
