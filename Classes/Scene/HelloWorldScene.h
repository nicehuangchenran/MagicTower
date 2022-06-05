//
//  MyHelloWorldScene.h
//  MagicTower
//
//  Created by 焦骜 on 2022/5/16.
//

#ifndef _HELLO_WORLD_SCENE_H_
#define _HELLO_WORLD_SCENE_H_

#include "cocos2d.h"

class HelloWorld :public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuItemSetting(cocos2d::Ref* PSender);
    void menuCloseCallback(cocos2d::Ref* PSender);
    void menuItemIntro(Ref* PSender);
    CREATE_FUNC(HelloWorld);
};


#endif // !_HELLO_WORLD_SCENE_H_
