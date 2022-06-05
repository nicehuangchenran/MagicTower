//
//  Introduction.hpp
//  MagicTower_utf_8
//
//  Created by 焦骜 on 2022/6/5.
//

#ifndef Introduction_hpp
#define Introduction_hpp
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

#endif /* Introduction_hpp */
