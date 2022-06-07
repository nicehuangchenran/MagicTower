#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include "Headers.h"
USING_NS_CC;

class GameMap :public TMXTiledMap {
public:
	Point tileCoordForPosition(Point position);
};

#endif // !_GAME_MAP_H_
