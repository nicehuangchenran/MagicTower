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
        return gameMapP;
    }
    else
    {
        delete gameMapP;
        return nullptr;
    }
}

Point GameMap::tileCoordForPosition(Point position) 
{
	return position;
}