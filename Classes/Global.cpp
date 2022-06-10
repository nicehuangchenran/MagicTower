#include "Headers.h"

Global* sGlobal = new Global;

Global::Global() :
	gameScene(nullptr), gameLayer(nullptr), controlLayer(nullptr), gameMap(nullptr), hero(nullptr), 
	currentLevel(0), heroSpawnTileCoord(Point{ 1, 1 })
{
	initEnemyMap();
};

void Global::initEnemyMap()
{
	std::ifstream in;
	in.open("..\\Resources\\EnemyInfo.txt", std::ios::in);
	if (!in.is_open()) { return; }
	int lef, rig;
	for (int i = 1; i <= ENEMY_NUM; ++i)
	{
		in >> lef >> rig;
		Enemy info;
		in >> info.name
		   >> info.blood
		   >> info.atk
		   >> info.def
		   >> info.gold
		   >> info.type
		   >> info.graphPosition.x
		   >> info.graphPosition.y;
		for (int j = lef; j <= rig; ++j)
		{
			enemyMap[j] = info;
		}
	}
	in.close();
}