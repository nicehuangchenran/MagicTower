#include "Teleport.h"


Teleport::Teleport(const ValueMap& dict, const int x, const int y)
{
	int rectX = dict.at("RecX").asInt();
	int rectY = dict.at("RecY").asInt();

	telePosition = Point(x+160, y);  // 传送门的位置，这里160是因为test_start是Scene场景而不是Layer
	
	targetID = dict.at("targetMap").asInt();  // 目标地图的层数
	//log("%d", targetID);
	targetHeroPosition = sGlobal -> gameMap -> positionForTileCoord(Point(dict.at("heroTileCoordX").asInt(),  // 目标地图英雄的起始坐标
	dict.at("heroTileCoordY").asInt()));
	targetHeroPosition.x += 160;

	auto teleport = Sprite::create("img/1.png", 
		Rect(rectX * OBJECT_SIZE, rectY*OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE) );  // 创建传送门精灵
	teleport->setAnchorPoint(Vec2::ZERO);
	teleport->setPosition(Vec2(telePosition));

	sGlobal->test_start->addChild(teleport,1);

}

Teleport::~Teleport()
{

}