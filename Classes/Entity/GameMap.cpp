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

Point GameMap::tileCoordForPosition(Point position)
{
    int x = position.x / this->getTileSize().width;
    int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
    return Point(x, y);
}