//
//  MyHelloWorldScene.hpp
//  MagicTower
//
//  Created by 焦骜 on 2022/5/16.
//

#ifndef HelloWorldScene_h
#define HelloWorldScene_h

#include "cocos2d.h"
class HelloWorld :public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuItemSetting(cocos2d::Ref* PSender);
    void menuCloseCallback(cocos2d::Ref* PSender);

    CREATE_FUNC(HelloWorld);
};


#endif /* HelloWorldScene_h */
