//
//  Introduction.h
//  MagicTower_utf_8
//
//  Created by 焦骜 on 2022/6/5.
//

#ifndef _INTRODUCTION_H_
#define _INTRODUCTION_H_

#include "ui/CocosGUI.h"
#include "cocos2d.h"

class Introduction:public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuItemBack(Ref* PSender);
    CREATE_FUNC(Introduction);
};

#endif // !_INTRODUCTION_H_
