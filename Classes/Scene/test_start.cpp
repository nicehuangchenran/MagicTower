//
//  test_start.cpp
//  MagicTower_utf_8
//
//  Created by 焦骜 on 2022/6/5.
//

#include "test_start.h"
#include "Headers.h"

USING_NS_CC;

test_start::test_start()
{
    sGlobal->test_start = this;
}

Scene* test_start::createScene()
{
    
    return test_start::create();
}

bool test_start::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //添加UI界面
    gameUI = Sprite::create("img/2.png");
    gameUI->setPosition(visibleSize / 2);
    addChild(gameUI);

    //添加地图
    char mapID[20];
    sprintf(mapID, "%d.tmx", sGlobal->currentLevel);
    log("%s", mapID);
    _tileMap = GameMap::create(mapID);
    
    _tileMap -> setAnchorPoint(Vec2(0.5,0.5));
    _tileMap -> setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 2));
    addChild(_tileMap, 0, 1);
    auto tileSize = _tileMap->getTileSize();
    auto tileMapSize = Size(_tileMap->getMapSize().width * tileSize.width, _tileMap->getMapSize().height * tileSize.height);
    
    //添加英雄
    auto hero = Hero::create(this, Vec2(0, 0));
    sGlobal->hero->setPosition(Vec2(sGlobal -> heroSpawnTileCoord));
    addChild(sGlobal->hero, 0);

    initHeroProperties();
    auto listenerkey = EventListenerKeyboard::create();

    listenerkey->onKeyPressed = ([=](EventKeyboard::KeyCode code, Event* event)
        {sGlobal->hero->move(code);
    flushHeroProperties();
            });
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    dispatcher->addEventListenerWithSceneGraphPriority(listenerkey, this);
    return true;
}

void test_start::initHeroProperties() {

    //初始化钥匙图案
    for (int i = 1; i <= 3; i++) {
        Sprite* keyImg = Sprite::create("img/1.png", Rect((i - 1) * 32, 0, 32, 32));
        keyImg->setPosition(610, 282 - i * 26);
        addChild(keyImg, 0);
        keyNum[i] = LabelTTF::create(" ", "fonts/Sonti.ttc", 16);
        keyNum[i]->setPosition(640, 282 - i * 26);
        addChild(keyNum[i], 0);
    }

    //初始化英雄属性
    bldNum = LabelTTF::create(StringUtils::format("%d", sGlobal->hero->bldNum()), "fonts/Sonti.ttc", 16);
    bldNum->setPosition(100, 337);
    addChild(bldNum);
    atkNum = LabelTTF::create(StringUtils::format("%d", sGlobal->hero->atkNum()), "fonts/Sonti.ttc", 16);
    atkNum->setPosition(100, 309);
    addChild(atkNum);
    defNum = LabelTTF::create(StringUtils::format("%d", sGlobal->hero->defNum()), "fonts/Sonti.ttc", 16);
    defNum->setPosition(100, 281);
    addChild(defNum);
    mnyNum = LabelTTF::create(StringUtils::format("%d", sGlobal->hero->mnyNum()), "fonts/Sonti.ttc", 16);
    mnyNum->setPosition(100, 253);
    addChild(mnyNum);
}

void test_start::flushHeroProperties() {
    for (int i = 1; i <= 3; i++) {
        keyNum[i]->setString(StringUtils::format("%d", sGlobal->hero->keyNum(i)));
    }
    bldNum->setString(StringUtils::format("%d", sGlobal->hero->bldNum()));
    atkNum->setString(StringUtils::format("%d", sGlobal->hero->atkNum()));
    defNum->setString(StringUtils::format("%d", sGlobal->hero->defNum()));
    mnyNum->setString(StringUtils::format("%d", sGlobal->hero->mnyNum()));
}