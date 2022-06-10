#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//游戏方格大小
const int OBJECT_SIZE = 32;

//怪物种类总数
const int ENEMY_NUM = 16;

//GID最大值
const int GID_MAX = 360;

//怪物攻击类型
enum ENEMY_TYPE
{
	NORMAL = 0, //物攻类怪物
	CRITICAL = 1, //暴击类怪物
	BOSS = 2 //真伤类怪物
};

//道具颜色
enum ITEM_COLOR
{
	YELLOW = 0,
	BLUE = 1,
	RED = 2,
	ULTRA = 3
};

//剑盾种类
enum WEAPON_TYPE
{
	IRON = 0, //铁剑盾
	SLIVER = 1, //银剑盾
	KNIGHT = 2, //骑士剑盾
	HOLY = 3, //神圣剑盾
};

//移动方向
enum DIRECTION
{
	UP = 13, //向上
	DOWN = 10, //向下
	LEFT = 11, //向左
	RIGHT = 12, //向右
};

//传送门种类
enum TELEPORT
{
	UPSTAIR = 0, //上楼
	DOWNSTAIR = 1, //下楼
};

//碰撞类型
enum COLLISION_TYPE
{
	COLLI_NONE = 1,
	COLLI_WALL = 2,
	COLLI_ENEMY = 3,
	COLLI_ITEM = 4,
	COLLI_DOOR = 5,
	COLLI_NPC = 6,
	COLLI_TELEPORT = 7,
};

//英雄初始数值
const int INIT_BLOOD = 400; //血量
const int INIT_ATK = 10; //攻击
const int INIT_DEF = 10; //防御
const int INIT_GOLD = 100; //金币

#endif // !_CONSTANTS_H_