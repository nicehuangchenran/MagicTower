#include "Headers.h"

GameMap::GameMap()
{
    if (sGlobal->gameMap) //ÊÍ·Å¿Õ¼ä
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
}

Point GameMap::tileCoordForPosition(Point position)
{
    int x = position.x / this->getTileSize().width;
    int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
    return Point(x, y);
}