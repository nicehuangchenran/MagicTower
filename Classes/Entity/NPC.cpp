#include "NPC.h"

NPC::NPC(const ValueMap& dict, const int& x, const int& y) {
	npcID = dict.at("name").asInt();
	type = dict.at("type").asString();
	imagePath = dict.at("image").asString();
	int x1 = dict.at("rectX").asInt(), y1 = dict.at("rectY").asInt();
	rect = Rect(x1, y1, OBJECT_SIZE, OBJECT_SIZE);
	Point position = Point(x, y);
	NPCTileCoord = sGlobal->gameMap->tileCoordForPosition(position);
	
	npcSprite = Sprite::create(imagePath, rect);
	npcSprite->setAnchorPoint(Point::ZERO);
	npcSprite->setPosition(position);
    
	//sGlobal->gameLayer->addChild(npcSprite, kZNPC);
	/*Animate* animation = sAnimationMgr->createAnimate(npcID);
	if (animation != NULL)
	{
		ActionInterval* action = RepeatForever::create(animation);
		npcSprite->runAction(action);
	}*/
}

NPC::~NPC() {

}

void NPC::meetWithHero() {
	//触发对话
}