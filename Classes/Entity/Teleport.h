#ifndef __TELEPORT_H__
#define __TELEPORT_H__

#include "cocos2d.h"
#include "Headers.h"
USING_NS_CC;

class Teleport:public Ref
{
public:
	Teleport(const ValueMap& dict,const int x, const int y);
	~Teleport();

	Point telePosition; // 传送门位置，Scene场景GL坐标，需要转换
	int targetID; // 目标地图层数，在hero.cpp中被获取然后切换场景
	Point targetHeroPosition;  // 目标地图英雄初始位置（Tile坐标）

};

#endif
