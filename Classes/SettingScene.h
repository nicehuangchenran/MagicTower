//
//  SettingScene.hpp
//  MagicTower
//
//  Created by 焦骜 on 2022/6/1.
//

#ifndef SettingScene_h
#define SettingScene_h
#include "ui/CocosGUI.h"
#include "cocos2d.h"

class Setting :public cocos2d::Scene
{
public:
    static bool isEffect;
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuItemSoundToggleCallback(cocos2d::Ref* PSender);
    void menuItemBack(cocos2d::Ref* Psender);
    void onChangedSlider(Ref* PSender, cocos2d::ui::Slider::EventType type);
    CREATE_FUNC(Setting);
};


#endif /* SettingScene_h */
