#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"
#include "ChangableObject.h"

USING_NS_CC;

class Enemy : public ChangableObject
{
public:
	Enemy(void);
	~Enemy(void);

	//怪物在TileMap上的位置
	Point enemyTileCoord;

	//怪物初始的图块ID
	int graphID;

	//怪物在字典中的index
	int dictIdx;
};

#endif // !_ENEMY_H_