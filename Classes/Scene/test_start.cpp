//
//  test_start.cpp
//  MagicTower_utf_8
//
//  Created by 焦骜 on 2022/6/5.
//

#include "test_start.h"
#include "Headers.h"

USING_NS_CC;

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
    _tileMap = GameMap::create("1.tmx");
    _tileMap -> setAnchorPoint(Vec2(0.5,0.5));
    _tileMap -> setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 2));
    addChild(_tileMap, 0, 1);
    auto tileSize = _tileMap->getTileSize();
    auto tileMapSize = Size(_tileMap->getMapSize().width * tileSize.width, _tileMap->getMapSize().height * tileSize.height);

    //添加英雄
    auto hero = Hero::create(this, Vec2(0, 0));
    sGlobal->hero->setPosition(Vec2(origin.x + OBJECT_SIZE * 10, origin.y));
    addChild(sGlobal->hero, 0);

    initHeroProperties();

    auto listenerkey = EventListenerKeyboard::create();

    listenerkey->onKeyPressed = ([=](EventKeyboard::KeyCode code, Event* event)
        {
            pauseOrContinue(code);
            if (Director::getInstance()->isPaused())
            {
                return;
            }
            sGlobal->hero->move(code);
            flushHeroProperties();
        });
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    dispatcher->addEventListenerWithSceneGraphPriority(listenerkey, this);
    return true;
}

void test_start::initHeroProperties() {

    //初始化钥匙图案
    for (int i = 0; i < 3; i++)
    {
        auto keyImg = Sprite::create("img/1.png", Rect(i * 32, 0, 32, 32));
        keyImg->setPosition(610, 256 - i * 26);
        addChild(keyImg, 0);
        keyNum[i] = LabelTTF::create(StringUtils::format("%d", sGlobal->hero->keyNum(i)), "fonts/Sonti.ttc", 16);
        keyNum[i]->setPosition(640, 256 - i * 26);
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
    floorNum= LabelTTF::create(StringUtils::format("%d", sGlobal->hero->floor), "fonts/Sonti.ttc", 16);
    floorNum->setPosition(104, 371);
    addChild(floorNum);
    swordName= LabelTTF::create(StringUtils::format("%s", sGlobal->hero->swordName().data()), "fonts/Sonti.ttc", 16);
    swordName->setPosition(635, 353);
    addChild(swordName); 
    shieldName = LabelTTF::create(StringUtils::format("%s", sGlobal->hero->shieldName().data()), "fonts/Sonti.ttc", 16);
    shieldName->setPosition(635, 295);
    addChild(shieldName);
}

void test_start::flushHeroProperties()
{
    for (int i = 0; i < 3; i++)
    {
        keyNum[i]->setString(StringUtils::format("%d", sGlobal->hero->keyNum(i)));
    }
    bldNum->setString(StringUtils::format("%d", sGlobal->hero->bldNum()));
    atkNum->setString(StringUtils::format("%d", sGlobal->hero->atkNum()));
    defNum->setString(StringUtils::format("%d", sGlobal->hero->defNum()));
    mnyNum->setString(StringUtils::format("%d", sGlobal->hero->mnyNum()));
    floorNum->setString(StringUtils::format("%d", sGlobal->hero->floor));
    swordName->setString(StringUtils::format("%s", sGlobal->hero->swordName().data()));
    shieldName->setString(StringUtils::format("%s", sGlobal->hero->shieldName().data()));
}

void test_start::pauseOrContinue(EventKeyboard::KeyCode code)
{
    if (code == EventKeyboard::KeyCode::KEY_P)
    {
        if (Director::getInstance()->isPaused())
        {
            Director::getInstance()->resume();
            removeChild(pauseWindow);
        }
        else
        {
            pauseWindow = Label::createWithTTF("Game Paused...\nPress \"P\" to Continue", "fonts/Marker Felt.ttf", 36);
            pauseWindow->setPosition(Director::getInstance()->getVisibleSize() / 2);
            pauseWindow->enableShadow(Color4B(166, 166, 166, 166), Size(5, 5)); //设置阴影效果
            pauseWindow->enableOutline(Color4B::RED, 5); //设置边框效果
            addChild(pauseWindow);
            Director::getInstance()->pause();
        }
    }
}