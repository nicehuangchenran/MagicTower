//
//  GameScene.cpp
//  MagicTower_utf_8
//
//  Created by 焦骜 on 2022/6/5.
//

#include "GameScene.h"
#include "Headers.h"

USING_NS_CC;

GameScene::GameScene()
{
    sGlobal->GameScene = this;
}

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
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
    if (sGlobal->curMaxLevel > sGlobal->currentLevel) {
        _tileMap = sGlobal->levels[sGlobal->currentLevel - 1];
        sGlobal->gameMap = _tileMap;
        _tileMap->setParent(nullptr);
        _tileMap->initObject();
        
    }
    else
        _tileMap = GameMap::create(mapID);
    
    _tileMap -> setAnchorPoint(Vec2(0.5,0.5));
    _tileMap -> setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 2));
    addChild(_tileMap, 0, 1);
    auto tileSize = _tileMap->getTileSize();
    auto tileMapSize = Size(_tileMap->getMapSize().width * tileSize.width, _tileMap->getMapSize().height * tileSize.height);
    //this->reorderChild(this->getChildByName("tel"), 2);
    //添加英雄

    //if (sGlobal->hero)    this->removeChild(sGlobal->hero);
    auto hero = Hero::create(this, Vec2(sGlobal->heroSpawnTileCoord));
    
    sGlobal->hero->setPosition(Vec2(sGlobal->heroSpawnTileCoord));
    addChild(hero, 0,"hero");


    /*
    if (hero->getParent())
        hero->setParent(nullptr);
    
    */
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

void GameScene::initHeroProperties() {

    //初始化钥匙图案
    for (auto i : { 0,1,2 })
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
    floorNum= LabelTTF::create(StringUtils::format("%d", sGlobal->currentLevel), "fonts/Sonti.ttc", 16);
    floorNum->setPosition(104, 371);
    addChild(floorNum);
    swordName= LabelTTF::create(StringUtils::format("%s", sGlobal->hero->swordName().data()), "fonts/Sonti.ttc", 16);
    swordName->setPosition(635, 353);
    addChild(swordName); 
    shieldName = LabelTTF::create(StringUtils::format("%s", sGlobal->hero->shieldName().data()), "fonts/Sonti.ttc", 16);
    shieldName->setPosition(635, 295);
    addChild(shieldName);
}

void GameScene::flushHeroProperties()
{
    for (auto i : { 0,1,2 })
    {
        keyNum[i]->setString(StringUtils::format("%d", sGlobal->hero->keyNum(i)));
    }
    bldNum->setString(StringUtils::format("%d", sGlobal->hero->bldNum()));
    atkNum->setString(StringUtils::format("%d", sGlobal->hero->atkNum()));
    defNum->setString(StringUtils::format("%d", sGlobal->hero->defNum()));
    mnyNum->setString(StringUtils::format("%d", sGlobal->hero->mnyNum()));
    floorNum->setString(StringUtils::format("%d", sGlobal->currentLevel));
    swordName->setString(StringUtils::format("%s", sGlobal->hero->swordName().data()));
    shieldName->setString(StringUtils::format("%s", sGlobal->hero->shieldName().data()));
}

void GameScene::pauseOrContinue(EventKeyboard::KeyCode code)
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
