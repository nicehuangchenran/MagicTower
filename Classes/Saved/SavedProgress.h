#ifndef _SAVED_PROGRESS_H_
#define _SAVED_PROGRESS_H_

#include "Headers.h"
USING_NS_CC;

using std::string;
using std::map;

class pos :public Node 
{
public:
	Vec2 pnt;
};

struct savedLevel 
{
	//GID->tileCoord
public:
	map<Point, int>* records[4];
};

class SavedProgress:public Ref 
{
public:
	SavedProgress(void);

	//保存已到达过的全部关卡
	void saveGame();
	//保存单个关卡
	void saveLevel(const GameScene* scene);
	
	map<Point, int>* saveObjects(const GameMap* map, const string& type);

	map<Point, int>* getObjects(const int& levelNum, const string& type);

	Map<int, GameMap>* levels;
};

#endif // !_SAVED_PROGRESS_H_
