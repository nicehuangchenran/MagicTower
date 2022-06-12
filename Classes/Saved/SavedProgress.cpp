#include "Headers.h"

SavedProgress::SavedProgress(void)
{
	sGlobal->saved = this;
}

void SavedProgress::saveGame() 
{
	const int& levelNum = sGlobal->currentLevel;
	for (int i = 1; i <= levelNum; i++) 
	{
		//此处saveEnemies的参数应为对应关卡
		//saveEnemies();
		//saveObject();
	}
}

void SavedProgress::saveLevel(const GameScene* scene)
{
	sGlobal->savedLevels[sGlobal->currentLevel - 1] = scene->_tileMap;
}

map<Point, int>* SavedProgress::saveObjects(const GameMap* map, const string& type) 
{
	auto info = new std::map<Point, int>;
	auto enemyLayer = sGlobal->gameMap->getLayer("enemy");
	Size s = enemyLayer->getLayerSize();
	for (int x = 0; x < s.width; x++)
	{
		for (int y = 0; y < s.height; y++)
		{
			int gid = enemyLayer->getTileGIDAt(Point(x, y));
			if (gid)
			{
				info->insert({ Point(x,y), gid });
			}
		}
	}
	return info;
}