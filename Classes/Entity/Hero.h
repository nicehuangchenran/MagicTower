#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"

USING_NS_CC;

class Hero :public Node {
public:
	Hero();
	~Hero();
	static Hero* create();
	bool init();
	

protected:
	Sprite* heroSprite;

};

#endif // !_HERO_H_