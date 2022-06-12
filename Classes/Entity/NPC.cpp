#include "Headers.h"

NPC::NPC(const ValueMap& dict, const int& x, const int& y) 
{
	npcID = dict.at("name").asInt();
	type = dict.at("type").asString();
	imagePath = "img/1.png";
	int x1 = dict.at("RecX").asInt(), y1 = dict.at("RecY").asInt();
	rect = Rect(x1 * OBJECT_SIZE, y1 * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE);
	Point position = Point(x + 160, y);
	NPCTileCoord = sGlobal->gameMap->tileCoordForPosition(position);

	npcSprite = Sprite::create(imagePath, rect);
	npcSprite->setAnchorPoint(Point::ZERO);
	npcSprite->setPosition(position);
	sGlobal->test_start->addChild(npcSprite, 1);

	Animate* action = Animate::create(npcAnimation(dict));
	npcSprite->runAction(action);
}

NPC::~NPC() {}

Animation* NPC::npcAnimation(const ValueMap& dict)
{
	const int kFrameNum = 4;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;
	int x1 = dict.at("RecX").asInt(), y1 = dict.at("RecY").asInt();
	for (int i = 0; i < kFrameNum; i++) {
		frame = SpriteFrame::create(StringUtils::format("img/1.png"), Rect((x1+i) * OBJECT_SIZE , y1 * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.2f);
	return animation;
}

int NPC::getNPCID() 
{
	return npcID;
}
