#pragma once
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// 方格大小
const int OBJECT_SIZE = 32;

// 道具颜色
const int ITEM_COLOR_YELLOW = 0;
const int ITEM_COLOR_BLUE = 1;
const int ITEM_COLOR_RED = 2;

//剑盾种类
const int WEAPON_TYPE_IRON = 0;
const int WEAPON_TYPE_SLIVER = 1;
const int WEAPON_TYPE_KNIGHT = 2;
const int WEAPON_TYPE_HOLY = 3;

//移动方向
const int DIRECTION_UP = 0;
const int DIRECTION_DOWN = 1;
const int DIRECTION_LEFT = 2;
const int DIRECTION_RIGHT = 3;

typedef enum
{
	kDown = 0,
	kLeft = 1,
	kRight = 2,
	kUp = 3,
	kNormal,
} HeroDirection;

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