#ifndef _TEST_START_H_
#define _TEST_START_H_

#include "cocos2d.h"
#include "GameMap.h"

class GameScene:public cocos2d::Scene
{
public:
    GameScene();
    GameMap* _tileMap;
    static cocos2d::Scene* createScene();
    virtual bool init();
    void initHeroProperties(); //初始化英雄信息显示
    void flushHeroProperties(); //更新英雄信息显示
    void pauseOrContinue(EventKeyboard::KeyCode code); //暂停

    LabelTTF* keyNum[4], * bldNum, * atkNum, * defNum, * mnyNum, *floorNum, *swordName, *shieldName;
    cocos2d::Sprite* gameUI;
    cocos2d::Label* pauseWindow;
    cocos2d::Label* weaponLabel;
    cocos2d::Label* heroLabel;
    cocos2d::Label* keyLabel;
    
    CREATE_FUNC(GameScene);
};

#endif // !_TEST_START_H_