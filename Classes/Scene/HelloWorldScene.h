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
    void menuItemSetting(cocos2d::Ref* PSender); //选项设置
    void menuCloseCallback(cocos2d::Ref* PSender); //退出游戏
    void menuItemIntro(Ref* PSender); //游戏说明
    void menuItemStart(Ref* PSender); //开始游戏
    CREATE_FUNC(HelloWorld);
};


#endif // !_HELLO_WORLD_SCENE_H_
