#pragma once
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <map>
// 
const int ObjectSize = 32;

// 道具颜色对应的数字
const int ITEM_COLOR_YELLOW = 1;
const int ITEM_COLOR_BLUE = 2;
const int ITEM_COLOR_RED = 3;

// 怪物名到怪物ID的映射
std::map<std::string, int> enemyID;

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