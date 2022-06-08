#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include "Headers.h"
USING_NS_CC;

class GameMap :public TMXTiledMap {
	// 为了方便调用不同层，使用cocos宏定义
	CC_SYNTHESIZE(TMXLayer*, floorLayer, FloorLayer);
	CC_SYNTHESIZE(TMXLayer*, wallLayer, WallLayer);
	CC_SYNTHESIZE(TMXLayer*, enemyLayer, EnemyLayer);
	CC_SYNTHESIZE(TMXLayer*, doorLayer, DoorLayer);
	CC_SYNTHESIZE(TMXLayer*, itemLayer, ItemLayer);
public:

	GameMap* create(const char* finepath);
	void mapInit();
	void initEnemy();
	void initObject();
	GameMap();
	Point tileCoordForPosition(Point position);
	
};

#endif // !_GAME_MAP_H_
