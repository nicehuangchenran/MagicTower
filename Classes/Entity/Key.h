#ifndef _KEY_H_
#define _KEY_H_

#include "cocos2d.h"
#include "ChangableObject.h"

USING_NS_CC;

class Key :public ChangableObject {
public:
	Key();
	~Key();
	void meetWithHero();

protected:
	Sprite* keySprite;

};

#endif // !_KEY_H_
