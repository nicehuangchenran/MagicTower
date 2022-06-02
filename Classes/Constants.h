#pragma once
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

const int ObjectSize = 32;

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

#endif