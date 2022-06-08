#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//游戏方格大小
const int OBJECT_SIZE = 32;

//怪物种类总数
const int ENEMY_NUM = 16;

//怪物攻击类型
const int ENEMY_TYPE_NORMAL = 0; //物攻类怪物
const int ENEMY_TYPE_CRITICAL = 1; //暴击类怪物
const int ENEMY_TYPE_BOSS = 2; //真伤类怪物

//道具颜色
const int ITEM_COLOR_YELLOW = 0; //黄色道具
const int ITEM_COLOR_BLUE = 1; //蓝色道具
const int ITEM_COLOR_RED = 2; //红色道具

//剑盾种类
const int WEAPON_TYPE_IRON = 0; //铁剑盾
const int WEAPON_TYPE_SLIVER = 1; //银剑盾
const int WEAPON_TYPE_KNIGHT = 2; //骑士剑盾
const int WEAPON_TYPE_HOLY = 3; //神圣剑盾

//移动方向


const int DIRECTION_DOWN = 10;
const int DIRECTION_UP = 13;
const int DIRECTION_RIGHT = 12;
const int DIRECTION_LEFT = 11;


const int DIRECTION_UP = 0; //向上
const int DIRECTION_DOWN = 1; //向下
const int DIRECTION_LEFT = 2; //向左
const int DIRECTION_RIGHT = 3; //向右

//英雄初始数值
const int INIT_BLOOD = 400; //血量
const int INIT_ATK = 10; //攻击
const int INIT_DEF = 10; //防御
const int INIT_GOLD = 100; //金币


//传送门种类
const int UP_TELEPORT = 0; //上楼
const int DOWN_TELEPORT = 1; //下楼

/*
typedef enum
{
	kDown = 0,
	kLeft = 1,
	kRight = 2,
	kUp = 3,
	kNormal,
} HeroDirection;
*/

typedef enum
{
	kNone = 1,
	kWall,
	kEnemy,
	kItem,
	kDoor,
	kNPC,
	kTeleport,
} CollisionType;

typedef enum
{
	aDown = 0,
	aLeft,
	aRight,
	aUp,
	aFight,
} AnimationKey;

enum
{
	kZMap = 0,
	kZNPC,
	kZTeleport,
	kZHero,
	kZTip,
};//GameLayer中各部分的显示zOrder及tag

enum
{
	kGameLayer = 0,
	kControlLayer,
	kFadeLayer,
};


#endif // !_CONSTANTS_H_