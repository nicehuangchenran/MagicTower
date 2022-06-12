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
      
        // 如果对象种类是store，标记本层有store位置（index）
        hasStore = false;
        if (type == "store")
        {
            hasStore = true;
            storeObject = dict;
            buyLayerOpen = false;
            //初始化商店图像
            string imagePath = "img/1.png";
            int x = storeObject.at("tileCoordX").asInt(), y = storeObject.at("tileCoordY").asInt();
            int x1 = storeObject.at("RecX").asInt(), y1 = storeObject.at("RecY").asInt();
            auto rect = Rect(x1 * OBJECT_SIZE, y1 * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE);
            Point position = Point(x * OBJECT_SIZE + 160, y * OBJECT_SIZE);
            auto storeSprite = Sprite::create(imagePath, rect);
            storeSprite->setAnchorPoint(Point::ZERO);
            storeSprite->setPosition(position);
            sGlobal->gameScene->addChild(storeSprite, 8);
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
            sGlobal->hero->removeChild(tipLabel, true);
        },
        nullptr);

    tipLabel->runAction(action);
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
    sGlobal->gameScene->flushHeroProperties();
    sGlobal->gameMap->removeChildByName("chooseWindow");
    chooseWindow = false;
}

void GameMap::closeInvincible(Ref* pSender)
{
    sGlobal->gameMap->removeChildByName("chooseWindow");
    chooseWindow = false;
}

//商店系统
void GameMap::initStore()
{
    if (buyLayerOpen)
    {
        return;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //初始化购买页面
    Sprite* buySprite = Sprite::create("img/6.png");

    Label* label = Label::create("商店", "fonts/arial.ttf", 20);

    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(20);
    auto item1 = MenuItemFont::create("100元提高5点攻击", CC_CALLBACK_1(GameMap::buyAtt, this));
    auto item2 = MenuItemFont::create("100元提高5点防御", CC_CALLBACK_1(GameMap::buyDef, this));
    auto item3 = MenuItemFont::create("100元获得200点血量", CC_CALLBACK_1(GameMap::buyBlood, this));
    auto item4 = MenuItemFont::create("退出", CC_CALLBACK_1(GameMap::buyExit, this));
    auto menu = Menu::create(item1, item2, item3,item4, NULL);
    menu->alignItemsVertically();

    auto layer = Layer::create();
    buySprite->setPosition(Vec2(visibleSize.width / 2 - 4 * OBJECT_SIZE, visibleSize.height / 2));
    buySprite->setAnchorPoint(Vec2(0.5, 0.5));
    layer->addChild(buySprite);
    menu->setPosition(Vec2(visibleSize.width / 2 - 4 * OBJECT_SIZE, visibleSize.height / 2));
    layer->addChild(menu);

    sGlobal->gameMap->addChild(layer, 10, "buyLayer");
    buyLayerOpen = true;
}

void GameMap::buyAtt(Ref*)
{
    sGlobal->hero->atk = 5 + sGlobal->hero->atk;
    sGlobal->hero->gold = sGlobal->hero->gold - 100;
    sGlobal->gameScene->flushHeroProperties();
    sGlobal->gameMap->removeChildByName("buyLayer");
    buyLayerOpen = false;
}

void GameMap::buyDef(Ref*)
{
    sGlobal->hero->def = sGlobal->hero->def + 5;
    sGlobal->hero->gold = sGlobal->hero->gold - 100;
    sGlobal->gameScene->flushHeroProperties();
    sGlobal->gameMap->removeChildByName("buyLayer");
    buyLayerOpen = false;
}

void GameMap::buyBlood(Ref*)
{
    sGlobal->hero->blood = sGlobal->hero->blood + 200;
    sGlobal->hero->gold = sGlobal->hero->gold - 100;
    sGlobal->gameScene->flushHeroProperties();
    sGlobal->gameMap->removeChildByName("buyLayer");
    buyLayerOpen = false;
}

void GameMap::buyExit(Ref*)
{
    sGlobal->gameMap->removeChildByName("buyLayer");
    buyLayerOpen = false;
}