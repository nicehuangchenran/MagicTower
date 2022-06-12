#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "Entity/Enemy.h"
#include "Constants.h"

using namespace cocos2d;

class GameMap;
class Hero;
class Teleport;
class GameScene;
class SavedProgress;

class Global
{

public:
	Global();

	//初始化怪物信息映射
	void initEnemyMap();

	//游戏结束
	void gameOver(const char* msg);

	//游戏场景
	GameScene *gameScene;

	//游戏地图
	GameMap *gameMap;

	//英雄
	Hero *hero;

	//目标地图的层数
	int currentLevel;

	//目前最高层数
	int curMaxLevel;

	//勇士出现的起始位置
	Vec2 heroSpawnTileCoord;
	
	// 怪物ID到怪物数据的映射
	std::map<int, Enemy> enemyMap;

	//当前存档
	//SavedProgress* saved;
	SavedProgress* saved;

	GameMap* savedLevels[LEVEL_NUM];

	bool paused; //返回标题
};

#endif // !_GLOBAL_H_
