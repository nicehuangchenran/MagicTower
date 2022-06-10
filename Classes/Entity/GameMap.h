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
	GameMap();
	static GameMap* create(const char* filePath);
	void mapInit();
	void initEnemy();
	void initObject();
	Point tileCoordForPosition(Point position);
	void showTip(const char* tip, Point startPosition);
	void onShowTipDone(Node* pSender);
	void deleteDoor(Vec2 position);
	void showInfo(const char* info, int time);
	Vector<Enemy*> enemyArray;
	//Map<int, Teleport*> teleportDict; // 传送门类待定义
	Map<int, NPC*> npcDict;  // 有bug，暂且搁置
};

#endif // !_GAME_MAP_H_
