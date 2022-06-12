#include "Headers.h"

Global* sGlobal = new Global;

Global::Global() :
	gameScene(nullptr), gameMap(nullptr), hero(nullptr), saved(nullptr), paused(0),
	currentLevel(1), curMaxLevel(0), heroSpawnTileCoord(Point{ OBJECT_SIZE*10, OBJECT_SIZE })
{
	initEnemyMap();
};

void Global::initEnemyMap()
{
	std::ifstream in;
	in.open("..\\Resources\\EnemyInfo.txt", std::ios::in);
	if (!in.is_open()) 
	{ 
		return; 
	}
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
		   >> (int&)(info.type)
		   >> info.graphPosition.x
		   >> info.graphPosition.y;
		for (int j = lef; j <= rig; ++j)
		{
			enemyMap[j] = info;
		}
	}
	in.close();
}

void Global::gameOver(const char* msg)
{
	auto label = LabelTTF::create(msg, "Arial", 72);
	label->enableShadow(Size(5,5), 0.5f, 0.5f);
	label->setColor(Color3B::RED);
	label->setPosition(Director::getInstance()->getVisibleSize() / 2);
	gameScene->addChild(label);

	gameScene->schedule(
		[=](float dlt)
		{
			gameScene->removeChild(label);
			gameScene->unschedule("gameOver");

			//Êý¾Ý»Ö¸´
			hero = nullptr;
			currentLevel = 1;
			curMaxLevel = 0;
			heroSpawnTileCoord = Point{ OBJECT_SIZE * 10, OBJECT_SIZE };

			Director::getInstance()->popToRootScene();
		},
		2.5f,"gameOver");
}