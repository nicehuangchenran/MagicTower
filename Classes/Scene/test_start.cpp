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

    //英雄信息
    heroLabel = Label::create(hero->getInfo(), "Arial", 25);
    heroLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    heroLabel->setPosition(90, 295);
    addChild(heroLabel);
    schedule([=](float dlt)
        {
            heroLabel->setString(hero->getInfo());
            if (0)
            {
                unschedule("infoDisplay");
            }
        },0.1f,"infoDisplay");

    auto listenerkey = EventListenerKeyboard::create();

    listenerkey->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event)
        {
            sGlobal->hero->move(code);
        };
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    dispatcher->addEventListenerWithSceneGraphPriority(listenerkey, this);
    return true;
}