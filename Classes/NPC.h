#ifndef _NPC_H_
#define _NPC_H_

#include "Headers.h"
USING_NS_CC;

class NPC :public Ref {
public:
	NPC(const ValueMap& dict, const int& x, const int& y);
	~NPC();
protected:
	Sprite* npcSprite;
	int npcID;
	Point NPCTileCoord;
	std::string imagePath;
	Rect rect;
	std::string type;
};

#endif // !_NPC_H_
