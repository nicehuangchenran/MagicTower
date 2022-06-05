#ifndef _CHANGABLE_OBJECT_H_
#define _CHANGABLE_OBJECT_H_

#include "cocos2d.h"

USING_NS_CC;

class ChangableObject :public Node {
public:
	ChangableObject();
	~ChangableObject();
	virtual void meetWithHero();
};

#endif // !_CHANGABLE_OBJECT_H_