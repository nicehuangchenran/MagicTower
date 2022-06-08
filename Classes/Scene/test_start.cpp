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
    
    _tileMap = TMXTiledMap::create("1.tmx");
    _tileMap -> setAnchorPoint(Vec2(0.5,0.5));
    _tileMap -> setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 2));
    addChild(_tileMap, 0, 1);
    auto tileSize = _tileMap->getTileSize();
    auto tileMapSize = Size(_tileMap->getMapSize().width * tileSize.width, _tileMap->getMapSize().height * tileSize.height);

    auto hero = Hero::create();

    sGlobal->hero =hero;
    sGlobal -> hero->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    addChild(sGlobal -> hero, 0);

    hero->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    addChild(hero, 0); 


    hero->fightWithEnemy(this, 1);
    auto listenerkey = EventListenerKeyboard::create();

    listenerkey->onKeyPressed = ([=](EventKeyboard::KeyCode code, Event* event)
        {sGlobal->hero->move(code);
            });
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    dispatcher->addEventListenerWithSceneGraphPriority(listenerkey, this);
    return true;
}
