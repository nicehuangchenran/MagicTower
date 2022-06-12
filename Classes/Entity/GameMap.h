#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include "Headers.h"

USING_NS_CC;

class NPC;

class GameMap :public TMXTiledMap 
{
	// 为了方便调用不同层，使用cocos宏定义
	CC_SYNTHESIZE(TMXLayer*, floorLayer, FloorLayer);
	CC_SYNTHESIZE(TMXLayer*, wallLayer, WallLayer);
	CC_SYNTHESIZE(TMXLayer*, enemyLayer, EnemyLayer);
	CC_SYNTHESIZE(TMXLayer*, doorLayer, DoorLayer);
	CC_SYNTHESIZE(TMXLayer*, itemLayer, ItemLayer);

public:
	GameMap();
	~GameMap();
	static GameMap* create(const char* filePath);
	void mapInit();
	void initEnemy();
	void initObject();
	Point tileCoordForPosition(Point position);  // GL坐标 -> tile坐标
	Point positionForTileCoord(Point tileCoord);  // tile坐标 -> GL坐标
	void showTip(const char* tip);
	void deleteDoor(Vec2 position);
	void showInfo(const char* info, int time);

	//无敌控制
	void chooseInvincible(); 
	void openInvincible(Ref* );
	void closeInvincible(Ref*);

	Vector<Enemy*> enemyArray;
	Map<int, Teleport*> teleportDict; // 传送门类
	Map<int, NPC*> npcDict;  // 有bug，暂且搁置
};

#endif // !_GAME_MAP_H_
