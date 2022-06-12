#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"
#include "Constants.h"

USING_NS_CC;

class Enemy : public Node
{
public:
	Enemy();
	~Enemy();

	//怪物在TileMap上的位置
	Point enemyTileCoord;

	std::string name; //怪物名称
	int blood; //怪物血量
	int atk; //怪物攻击力
	int def; //怪物防御力
	int gold; //怪物掉落金币
	ENEMY_TYPE type; //怪物类型
	Vec2 graphPosition; //在素材图片中的位置
	int startGID;
	int index;

	Enemy& operator =(const Enemy& e);
};

#endif // !_ENEMY_H_