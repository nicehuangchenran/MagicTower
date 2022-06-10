#include "Headers.h"

GameMap::GameMap()
{
    if (sGlobal->gameMap) //释放空间
    {
        delete sGlobal->gameMap;
    }
	sGlobal->gameMap = this;
}

GameMap* GameMap::create(const char* filePath)
{
    GameMap* gameMapP = new GameMap();
    if (gameMapP->initWithTMXFile(filePath))
    {
        gameMapP->mapInit();
        return gameMapP;
    }
    else
    {
        delete gameMapP;
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
    //initObject();
}

void GameMap::initEnemy()
{

    enemyLayer = this->getLayer("enemy");

    Size s = enemyLayer->getLayerSize();


    for (int x = 0; x < s.width; x++)
    {
        for (int y = 0; y < s.height; y++)
        {
            int gid = enemyLayer->getTileGIDAt(Point(x, y));
            if (gid != 0)
            {
                Enemy* enemy = new Enemy();


                enemy->graphPosition = Point(x, y);


                enemy->startGID = gid;

                //这一步有bug，暂且搁置
                //enemyArray.pushBack(enemy);
            }
        }
    }
}

void GameMap::initObject() {
    TMXObjectGroup* group = this->objectGroupNamed("object");
    const ValueVector& objects = group->getObjects();
    for (ValueVector::const_iterator it = objects.begin(); it != objects.end(); it++) {
        const ValueMap& dict = (*it).asValueMap();
        int x = dict.at("x").asInt();
        int y = dict.at("y").asInt();
        Point tileCoord = tileCoordForPosition(Point(x, y));
        int index = tileCoord.x + tileCoord.y * this->getMapSize().width;
        std::string type = dict.at("type").asString();
        if (type == "npc") {
            NPC* npc = new NPC(dict, x, y);
            npcDict.insert(index, npc);
        }
    }
}

Point GameMap::tileCoordForPosition(Point position)
{
    int x = position.x / this->getTileSize().width;
    int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
    return Point(x, y);
}

void GameMap::showTip(const char* tip, Point startPosition) {
    //新建一个文本标签
    LabelTTF* tipLabel = LabelTTF::create(tip, "Arial", 20);

    tipLabel->setPosition(startPosition + Point(16, 16));

    this->addChild(tipLabel, kZTip, kZTip);

    //定义动画效果
    Action* action = Sequence::create(
        MoveBy::create(0.5f, Point(0, 32)),
        DelayTime::create(0.5f), FadeOut::create(0.2f),
        CallFuncN::create(CC_CALLBACK_1(GameMap::onShowTipDone, this)),
        NULL);

    tipLabel->runAction(action);
}

void GameMap::onShowTipDone(Node* pSender) {
    //删掉文本标签
    this->getChildByTag(kZTip)->removeFromParentAndCleanup(true);
}

void GameMap::showInfo(const char* info, int time) {
    auto label = Label::createWithTTF(info, "fonts/Marker Felt.ttf", 36);
    label->setPosition(100, 200); //设置标签位置
    label->enableShadow(Color4B::GREEN, Size(10, 10)); //设置阴影效果
    label->enableOutline(Color4B::RED, 3); //设置边框效果
    this->addChild(label, 0); //加入到场景中
    Sleep(time);
    this->removeChild(label);
}