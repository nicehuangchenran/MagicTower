#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "Singleton.h"
#include "Entity/Enemy.h"

using namespace cocos2d;

class GameScene;
class GameLayer;
class GameMap;
class Hero;
class ControlLayer;
class Teleport;
class test_start;

class Global
{

public:
	Global();

	//初始化怪物信息映射
	void initEnemyMap();

	//游戏场景
	test_start *test_start;

	//游戏主图层
	GameLayer *gameLayer;

	//控制层
	ControlLayer *controlLayer;

	//游戏地图
	GameMap *gameMap;

	//勇士
	Hero *hero;

	//目标地图的层数
	int currentLevel = 1;

	//勇士出现的起始位置
	Vec2 heroSpawnTileCoord;
	
	// 怪物ID到怪物数据的映射
	std::map<int, Enemy> enemyMap;
};

#endif // !_GLOBAL_H_
