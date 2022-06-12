#include "Headers.h"

GameMap::GameMap()
{
	sGlobal->gameMap = this;
}

GameMap::~GameMap() {}

GameMap* GameMap::create(const char* filePath)
{
    auto gameMapP = new GameMap();
    if (gameMapP->initWithTMXFile(filePath))
    {
        gameMapP->autorelease();
        gameMapP->mapInit();
        return gameMapP;
    }
    else
    {
        return nullptr;
    }
}

void GameMap::mapInit()
{
    floorLayer = this->getLayer("floor");
    wallLayer = this->getLayer("wall");
    itemLayer = this->getLayer("item");
    doorLayer = this->getLayer("door");

    initEnemy();
    initObject();
}

void GameMap::initEnemy()
{
    enemyLayer = this->getLayer("enemy");
  
    Size s = enemyLayer->getLayerSize();

    //添加怪物动画
    for (int x = 0; x < s.width; x++)
    {
        for (int y = 0; y < s.height; y++)
        {
            int gid = enemyLayer->getTileGIDAt(Point(x, y));
            if (gid)
            {
                schedule([=](float dlt)
                    {
                        int gid = enemyLayer->getTileGIDAt(Point(x, y));
                        if (gid)
                        {
                            gid++;
                            if (gid % 4 == 1)
                            {
                                gid -= 4;
                            }
                            enemyLayer->setTileGID(gid, Point(x, y));
                        }
                        else
                        {
                            unschedule("enemyAnimationAt" + Value(x).asString() + ',' + Value(y).asString());
                        }
                    }
                , 0.2f, "enemyAnimationAt" + Value(x).asString() + ',' + Value(y).asString());
            }
        }
    }
}

void GameMap::initObject()
{
    auto group = this->objectGroupNamed("object");
    const ValueVector& objects = group->getObjects();
    for (auto obj : objects)
    {
        const ValueMap& dict = obj.asValueMap();
        int x = dict.at("x").asInt();
        int y = dict.at("y").asInt();
        auto tileCoord = tileCoordForPosition(Point(x, y));
        int index = tileCoord.x + tileCoord.y * this->getMapSize().width;
        std::string type = dict.at("type").asString();
      
        // 如果对象种类是npc，创建对象并加入npcDict中
        if (type == "NPC") 
        {
            auto npc = new NPC(dict, x, y);
            npcDict.insert(index, npc);
        }
      
        // 如果对象种类是teleport，创建对象并加入teleportDict中
        if (type == "teleport")
        {
            auto tele = new Teleport(dict, x, y);
            teleportDict.insert(index, tele);
        }

        // 如果对象种类是store，在地图上创建store图块
        if (type == "store")
        {
            ;
        }
    }
}

Point GameMap::tileCoordForPosition(Point position)
{
    int x = position.x / this->getTileSize().width;
    int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
    return Point(x, y);
}

Point GameMap::positionForTileCoord(Point tileCoord)
{
    Point pos = Point((tileCoord.x * this->getTileSize().width), ((this->getMapSize().height - tileCoord.y - 1) * this->getTileSize().height));
    return pos;
}

void GameMap::showTip(const char* tip)
{
    //添加一个文本标签
    auto tipLabel = LabelTTF::create(tip, "Arial", 20);
    tipLabel->setPosition(16, 16); //设置位置
    sGlobal->hero->addChild(tipLabel);

    //定义动画效果
    Action* action = Sequence::create(
        MoveBy::create(0.5f, Point(0, 32)),
        DelayTime::create(0.5f),
        FadeOut::create(0.3f),
        [=]() 
        {
            sGlobal->hero->removeChild(tipLabel);
        },
        nullptr);

    tipLabel->runAction(action);
}

void GameMap::showInfo(const char* info, int time)
{
    auto label = Label::createWithTTF(info, "fonts/Marker Felt.ttf", 24);
    label->setPosition(16, 54); //设置标签位置
    label->enableShadow(Color4B(166, 166, 166, 166), Size(3, 3)); //设置阴影效果
    label->enableOutline(Color4B::RED, 2); //设置边框效果
    sGlobal->hero->addChild(label, 0); //加到英雄身上（加在this会被挡住）

    sGlobal->hero->isStopping = false;
    schedule([=](float dlt)
        {
            sGlobal->hero->isStopping = true;
            sGlobal->hero->removeChild(label);
            unschedule("tip");
        }
    , time / 1000.0f, "tip");
}

void GameMap::chooseInvincible()
{
    if (chooseWindow)
    {
        return;
    }
    auto item1 = MenuItemFont::create("开启无敌", CC_CALLBACK_1(GameMap::openInvincible, this));
    auto item2 = MenuItemFont::create("取消", CC_CALLBACK_1(GameMap::closeInvincible, this));
    item1->setFontName("fonts/arial.ttf");
    item2->setFontName("fonts/arial.ttf");

    //添加菜单
    auto menu = Menu::create(item1, item2, nullptr);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(-80, 128));
    sGlobal->gameMap->addChild(menu, 0, "chooseWindow");
    chooseWindow = true;
}

void GameMap::openInvincible(Ref* pSender)
{
    sGlobal->hero->atk = 999;
    sGlobal->hero->def = 999;
    sGlobal->hero->blood = 9999;
    sGlobal->hero->gold = 9999;
    for (auto i : { YELLOW,BLUE,RED })
    {
        sGlobal->hero->key[i] = 100;
    }
    sGlobal->test_start->flushHeroProperties();
    sGlobal->gameMap->removeChildByName("chooseWindow");
    chooseWindow = false;
}

void GameMap::closeInvincible(Ref* pSender)
{
    sGlobal->gameMap->removeChildByName("chooseWindow");
    chooseWindow = false;
}