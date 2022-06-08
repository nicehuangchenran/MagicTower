#ifndef _POTION_H_
#define _POTION_H_

#include "cocos2d.h"
#include "ChangableObject.h"

USING_NS_CC;

class Potion :public ChangableObject {
public:
	Potion();
	~Potion();
	void meetWithHero();

private:
	Sprite* spritePotion;

};

#endif // !_POTION_H_
