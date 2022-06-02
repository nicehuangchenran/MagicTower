#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "Headers.h"
#include "Singleton.h"

using namespace cocos2d;

class GameScene;
class GameLayer;
class GameMap;
class Hero;
class ControlLayer;

class Global : public Singleton<Global> {
public:
	Global(void) :
		gameScene(NULL), gameLayer(NULL), controlLayer(NULL), gameMap(NULL), hero(NULL),
		currentLevel(0), heroSpawnTileCoord(Point{ 1, 1 }) {};

	//游戏场景
	GameScene *gameScene;

	//游戏主图层
	GameLayer *gameLayer;

	//控制层
	ControlLayer *controlLayer;

	//游戏地图
	GameMap *gameMap;

	//勇士
	Hero *hero;

	//目标地图的层数
	int currentLevel;

	//勇士出现的起始位置
	Point heroSpawnTileCoord;
};

#define sGlobal Global::instance()

#endif // !_GLOBAL_H_
