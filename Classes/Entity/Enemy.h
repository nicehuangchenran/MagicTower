#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"
#include "ChangableObject.h"
#include "Constants.h"

USING_NS_CC;

class Enemy : public ChangableObject
{
public:
	Enemy();
	~Enemy();

	//怪物在TileMap上的位置
	Point enemyTileCoord;

	//怪物初始的图块ID
	int graphID;

	//怪物在字典中的index
	int dictIdx;

	std::string name; //怪物名称
	int blood; //怪物血量
	int atk; //怪物攻击力
	int def; //怪物防御力
	int gold; //怪物掉落金币
	ENEMY_TYPE type; //怪物类型
	Vec2 graphPosition; //在素材图片中的位置

	
	int startGID;

	
	int index;

	Enemy& operator =(const Enemy& e)
	{
		this->blood = e.blood;
		this->atk = e.atk;
		this->def = e.def;
		this->gold = e.gold;
		this->type = e.type;
		this->graphPosition = e.graphPosition;
		return *this;
	}
};

#endif // !_ENEMY_H_