#ifndef _TEST_START_H_
#define _TEST_START_H_

#include "cocos2d.h"
#include "Entity/GameMap.h"

class test_start:public cocos2d::Scene
{
public:
    GameMap* _tileMap;
    static cocos2d::Scene* createScene();
    virtual bool init();
    void initHeroProperties(); //��ʼ��Ӣ����Ϣ��ʾ
    void flushHeroProperties(); //����Ӣ����Ϣ��ʾ
    void pauseOrContinue(EventKeyboard::KeyCode code); //��ͣ

    LabelTTF* keyNum[4], * bldNum, * atkNum, * defNum, * mnyNum, *floorNum, *swordName, *shieldName;
    cocos2d::Sprite* gameUI;
    cocos2d::Label* pauseWindow;
    cocos2d::Label* weaponLabel;
    cocos2d::Label* heroLabel;
    cocos2d::Label* keyLabel;
    
    CREATE_FUNC(test_start);
};

#endif // !_TEST_START_H_
